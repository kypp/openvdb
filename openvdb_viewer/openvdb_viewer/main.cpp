#include "openvdb\viewer\Viewer.h"



void main() {
	openvdb::initialize();
	auto viewer = openvdb_viewer::init("sabaka");


	openvdb::GridCPtrVec vec;

	for (std::string name : {"fire.vdb", "bunny.vdb", "bunny_cloud.vdb", "dragon.vdb", "utahteapot.vdb"}) {
		// Create a VDB file object.
		openvdb::io::File file(name);
		// Open the file.  This reads the file header, but not any grids.
		file.open();

		openvdb::GridBase::Ptr baseGrid;
		for (openvdb::io::File::NameIterator nameIter = file.beginName();
			nameIter != file.endName(); ++nameIter)
		{
			baseGrid = file.readGrid(nameIter.gridName());
		}
		file.close();

		//openvdb::FloatGrid::Ptr grid = openvdb::gridPtrCast<openvdb::FloatGrid>(baseGrid);
		vec.push_back(baseGrid);
	}
	std::cout << vec.front()->memUsage() << "\n";

	viewer.view(vec);
}