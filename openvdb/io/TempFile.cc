///////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2012-2017 DreamWorks Animation LLC
//
// All rights reserved. This software is distributed under the
// Mozilla Public License 2.0 ( http://www.mozilla.org/MPL/2.0/ )
//
// Redistributions of source code must retain the above copyright
// and license notice and the following restrictions and disclaimer.
//
// *     Neither the name of DreamWorks Animation nor the names of
// its contributors may be used to endorse or promote products derived
// from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// IN NO EVENT SHALL THE COPYRIGHT HOLDERS' AND CONTRIBUTORS' AGGREGATE
// LIABILITY FOR ALL CLAIMS REGARDLESS OF THEIR BASIS EXCEED US$250.00.
//
///////////////////////////////////////////////////////////////////////////

/// @file TempFile.cc

#include "TempFile.h"

#include <openvdb/Exceptions.h>
#include <fstream> // for std::filebuf
#include <cstdio> // for std::tmpnam(), L_tmpnam, P_tmpdir
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#ifndef DWA_BOOST_VERSION
#define DWA_BOOST_VERSION (10 * BOOST_VERSION)
#endif


namespace openvdb {
OPENVDB_USE_VERSION_NAMESPACE
namespace OPENVDB_VERSION_NAME {
namespace io {

struct TempFile::TempFileImpl
{
    const std::string& filename() const { return mPath; }

    bool is_open() const { return mBuffer.is_open(); }

    /// @internal boost::filesystem::unique_path(), etc. might be useful here,
    /// but as of 9/2014, Houdini ships without the Boost.Filesystem library,
    /// which makes it much less convenient to use that library.
    // Use only standard library routines; no POSIX.

    TempFileImpl(std::ostream& os) { this->init(os); }

    void init(std::ostream& os)
    {
        char fnbuf[L_tmpnam];
        const char* filename = std::tmpnam(fnbuf);
        if (!filename) {
            OPENVDB_THROW(IoError, "failed to generate name for temporary file");
        }
        /// @todo This is not safe, since another process could open a file
        /// with this name before we do.  Unfortunately, there is no safe,
        /// portable way to create a temporary file.
        mPath = filename;

        const std::ios_base::openmode mode = (std::ios_base::out | std::ios_base::binary);
        os.rdbuf(mBuffer.open(mPath.c_str(), mode));
        if (!os.good()) {
            OPENVDB_THROW(IoError, "failed to open temporary file " + mPath);
        }
    }

    void close() { mBuffer.close(); }

    std::string mPath;
    std::filebuf mBuffer;

private:
    TempFileImpl(const TempFileImpl&); // disable copying
    TempFileImpl& operator=(const TempFileImpl&); // disable assignment
};


TempFile::TempFile(): std::ostream(nullptr), mImpl(new TempFileImpl(*this)) {}
TempFile::~TempFile() { this->close(); }
const std::string& TempFile::filename() const { return mImpl->filename(); }
bool TempFile::is_open() const { return mImpl->is_open(); }
void TempFile::close() { mImpl->close(); }

} // namespace io
} // namespace OPENVDB_VERSION_NAME
} // namespace openvdb

// Copyright (c) 2012-2017 DreamWorks Animation LLC
// All rights reserved. This software is distributed under the
// Mozilla Public License 2.0 ( http://www.mozilla.org/MPL/2.0/ )
