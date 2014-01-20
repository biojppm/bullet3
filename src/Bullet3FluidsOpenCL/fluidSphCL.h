//this file is autogenerated using stringify.bat (premake --stringify) in the build folder of this project
static const char* fluidSphCL= \
"/*\n"
"BulletFluids \n"
"Copyright (c) 2012 Jackson Lee\n"
"This software is provided 'as-is', without any express or implied warranty.\n"
"In no event will the authors be held liable for any damages arising from the use of this software.\n"
"Permission is granted to anyone to use this software for any purpose, \n"
"including commercial applications, and to alter it and redistribute it freely, \n"
"subject to the following restrictions:\n"
"1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.\n"
"2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.\n"
"3. This notice may not be removed or altered from any source distribution.\n"
"*/\n"
"#ifdef cl_amd_printf\n"
"	#pragma OPENCL EXTENSION cl_amd_printf : enable\n"
"#endif\n"
"typedef float b3Scalar;\n"
"typedef float4 b3Vector3;\n"
"#define b3Max max\n"
"#define b3Min min\n"
"//Note that these are vector3 functions -- OpenCL functions are vector4 functions\n"
"inline b3Scalar b3Vector3_length2(b3Vector3 v) { return v.x*v.x + v.y*v.y + v.z*v.z; }\n"
"inline b3Scalar b3Vector3_dot(b3Vector3 a, b3Vector3 b) { return a.x*b.x + a.y*b.y + a.z*b.z; }\n"
"inline b3Vector3 b3Vector3_normalize(b3Vector3 v)\n"
"{\n"
"	b3Scalar length2 = b3Vector3_length2(v);\n"
"	if( length2 != (b3Scalar)0.0f ) v /= sqrt(length2);\n"
"	\n"
"	return v;\n"
"}\n"
"//Defined in b3FluidSortingGrid.h\n"
"#define INVALID_FIRST_INDEX -1\n"
"#define INVALID_LAST_INDEX -2\n"
"//Syncronize with 'struct b3FluidSphParametersGlobal' in b3FluidSphParameters.h\n"
"typedef struct\n"
"{\n"
"	b3Scalar m_timeStep;\n"
"	b3Scalar m_simulationScale;\n"
"	b3Scalar m_sphSmoothRadius;\n"
"	b3Scalar m_sphRadiusSquared;\n"
"	b3Scalar m_poly6KernCoeff;\n"
"	b3Scalar m_spikyKernGradCoeff;\n"
"	b3Scalar m_viscosityKernLapCoeff;\n"
"	b3Scalar m_initialSum;\n"
"} b3FluidSphParametersGlobal;\n"
"//Syncronize with 'struct b3FluidSphParametersLocal' in b3FluidSphParameters.h\n"
"typedef struct\n"
"{\n"
"	b3Vector3 m_aabbBoundaryMin;\n"
"	b3Vector3 m_aabbBoundaryMax;\n"
"	int m_enableAabbBoundary;\n"
"	b3Vector3 m_gravity;\n"
"	b3Scalar m_sphAccelLimit;\n"
"	b3Scalar m_speedLimit;\n"
"	b3Scalar m_viscosity;\n"
"	b3Scalar m_restDensity;\n"
"	b3Scalar m_sphParticleMass;\n"
"	b3Scalar m_stiffness;\n"
"	b3Scalar m_particleDist;\n"
"	b3Scalar m_particleRadius;\n"
"	b3Scalar m_particleMargin;\n"
"	b3Scalar m_particleMass;\n"
"	b3Scalar m_boundaryStiff;\n"
"	b3Scalar m_boundaryDamp;\n"
"	b3Scalar m_boundaryFriction;\n"
"	b3Scalar m_boundaryRestitution;\n"
"	b3Scalar m_boundaryErp;\n"
"} b3FluidSphParametersLocal;\n"
"//#define B3_ENABLE_FLUID_SORTING_GRID_LARGE_WORLD_SUPPORT	//Ensure that this is also #defined in b3FluidSortingGrid.h\n"
"#ifdef B3_ENABLE_FLUID_SORTING_GRID_LARGE_WORLD_SUPPORT	\n"
"	typedef unsigned long b3FluidGridUint64;\n"
"	typedef b3FluidGridUint64 b3FluidGridCombinedPos;	//Range must contain B3_FLUID_GRID_COORD_RANGE^3\n"
"	#define B3_FLUID_GRID_COORD_RANGE 2097152		//2^21\n"
"	\n"
"	inline void splitCombinedPosition(b3FluidGridUint64 resolutionX, b3FluidGridUint64 resolutionY, \n"
"										b3FluidGridUint64 value, int* out_x, int* out_y, int* out_z)\n"
"	{\n"
"		b3FluidGridUint64 cellsPerLine = resolutionX;\n"
"		b3FluidGridUint64 cellsPerPlane = resolutionX * resolutionY;\n"
"		\n"
"		b3FluidGridUint64 x = value % cellsPerLine;\n"
"		b3FluidGridUint64 z = value / cellsPerPlane;\n"
"		b3FluidGridUint64 y = (value - z*cellsPerPlane) / cellsPerLine;\n"
"		\n"
"		*out_x = (int)x;\n"
"		*out_z = (int)z;\n"
"		*out_y = (int)y;\n"
"	}\n"
"#else\n"
"	typedef unsigned int b3FluidGridCombinedPos;		//Range must contain B3_FLUID_GRID_COORD_RANGE^3\n"
"	#define B3_FLUID_GRID_COORD_RANGE 1024			//2^10	\n"
"	\n"
"	inline void splitCombinedPosition(int resolutionX, int resolutionY, int value, int* out_x, int* out_y, int* out_z)\n"
"	{\n"
"		int x = value % resolutionX;\n"
"		int z = value / (resolutionX*resolutionY);\n"
"		int y = (value - z*resolutionX*resolutionY) / resolutionX;\n"
"		\n"
"		*out_x = (int)x;\n"
"		*out_z = (int)z;\n"
"		*out_y = (int)y;\n"
"	}\n"
"#endif\n"
"typedef int b3FluidGridCoordinate;\n"
"#define B3_FLUID_GRID_COORD_RANGE_HALVED B3_FLUID_GRID_COORD_RANGE/2\n"
"typedef struct\n"
"{\n"
"	int m_firstIndex;\n"
"	int m_lastIndex;\n"
"	\n"
"} b3FluidGridIterator;\n"
"//Since the hash function used to determine the 'value' of particles is simply \n"
"//(x + y*CELLS_PER_ROW + z*CELLS_PER_PLANE), adjacent cells have a value \n"
"//that is 1 greater and lesser than the current cell. \n"
"//This makes it possible to query 3 cells simultaneously(as a 3 cell bar extended along the x-axis) \n"
"//by using a 'binary range search' in the range [current_cell_value-1, current_cell_value+1]. \n"
"//Furthermore, as the 3 particle index ranges returned are also adjacent, it is also possible to \n"
"//stitch them together to form a single index range.\n"
"#define b3FluidSortingGrid_NUM_FOUND_CELLS_GPU 9\n"
"typedef struct\n"
"{\n"
"	b3FluidGridIterator m_iterators[b3FluidSortingGrid_NUM_FOUND_CELLS_GPU];\n"
"	\n"
"} b3FluidSortingGridFoundCellsGpu;		//b3FluidSortingGrid::FoundCellsGpu in b3FluidSortingGrid.h\n"
"typedef struct \n"
"{\n"
"	b3FluidGridCombinedPos m_value;\n"
"	int m_index;\n"
"	\n"
"} b3FluidGridValueIndexPair;\n"
"typedef struct\n"
"{\n"
"	b3FluidGridCoordinate x;		\n"
"	b3FluidGridCoordinate y;\n"
"	b3FluidGridCoordinate z;\n"
"	b3FluidGridCoordinate padding;\n"
"	\n"
"} b3FluidGridPosition;\n"
"b3FluidGridPosition getDiscretePosition(b3Scalar cellSize, b3Vector3 position)	//b3FluidSortingGrid::getDiscretePosition()\n"
"{\n"
"	b3Vector3 discretePosition = position / cellSize;\n"
"	\n"
"	b3FluidGridPosition result;\n"
"	result.x = (b3FluidGridCoordinate)( (position.x >= 0.0f) ? discretePosition.x : floor(discretePosition.x) );\n"
"	result.y = (b3FluidGridCoordinate)( (position.y >= 0.0f) ? discretePosition.y : floor(discretePosition.y) );\n"
"	result.z = (b3FluidGridCoordinate)( (position.z >= 0.0f) ? discretePosition.z : floor(discretePosition.z) );\n"
"	\n"
"	return result;\n"
"}\n"
"b3FluidGridCombinedPos getCombinedPosition(b3FluidGridPosition quantizedPosition)	//b3FluidGridPosition::getCombinedPosition()\n"
"{\n"
"	b3FluidGridCoordinate signedX = quantizedPosition.x + B3_FLUID_GRID_COORD_RANGE_HALVED;\n"
"	b3FluidGridCoordinate signedY = quantizedPosition.y + B3_FLUID_GRID_COORD_RANGE_HALVED;\n"
"	b3FluidGridCoordinate signedZ = quantizedPosition.z + B3_FLUID_GRID_COORD_RANGE_HALVED;\n"
"	\n"
"	b3FluidGridCombinedPos unsignedX = (b3FluidGridCombinedPos)signedX;\n"
"	b3FluidGridCombinedPos unsignedY = (b3FluidGridCombinedPos)signedY * B3_FLUID_GRID_COORD_RANGE;\n"
"	b3FluidGridCombinedPos unsignedZ = (b3FluidGridCombinedPos)signedZ * B3_FLUID_GRID_COORD_RANGE * B3_FLUID_GRID_COORD_RANGE;\n"
"	\n"
"	return unsignedX + unsignedY + unsignedZ;\n"
"}\n"
"__kernel void generateValueIndexPairs(__global b3Vector3* fluidPositions, __global b3FluidGridValueIndexPair* out_pairs, \n"
"										b3Scalar cellSize, int numFluidParticles)\n"
"{\n"
"	int index = get_global_id(0);\n"
"	if(index >= numFluidParticles) return;\n"
"	\n"
"	b3FluidGridValueIndexPair result;\n"
"	result.m_index = index;\n"
"	result.m_value = getCombinedPosition( getDiscretePosition(cellSize, fluidPositions[index]) );\n"
"	\n"
"	out_pairs[index] = result;\n"
"}\n"
"__kernel void rearrangeParticleArrays(__global b3FluidGridValueIndexPair* sortedPairs, __global b3Vector3* rearrange, \n"
"										__global b3Vector3* temporary, int numFluidParticles)\n"
"{\n"
"	int index = get_global_id(0);\n"
"	if(index >= numFluidParticles) return;\n"
"	\n"
"	//\n"
"	int oldIndex = sortedPairs[index].m_index;\n"
"	int newIndex = index;\n"
"	\n"
"	temporary[newIndex] = rearrange[oldIndex];\n"
"}\n"
"__kernel void markUniques(__global b3FluidGridValueIndexPair* valueIndexPairs, __global int* out_retainValueAtThisIndex, int numFluidParticles)\n"
"{\n"
"	int index = get_global_id(0);\n"
"	if(index >= numFluidParticles) return;\n"
"	\n"
"	int lastValidIndex = numFluidParticles - 1;\n"
"	\n"
"	//Retain if the next particle has a different b3FluidGridCombinedPos(is in another cell)\n"
"	int isRetained = (index < lastValidIndex) ? (valueIndexPairs[index].m_value != valueIndexPairs[index+1].m_value) : 1;\n"
"	\n"
"	out_retainValueAtThisIndex[index] = isRetained;\n"
"}\n"
"__kernel void storeUniquesAndIndexRanges(__global b3FluidGridValueIndexPair* valueIndexPairs, __global int* retainValue, __global int* scanResults, \n"
"							__global b3FluidGridCombinedPos* out_sortGridValues, __global b3FluidGridIterator* out_iterators, int numFluidParticles)\n"
"{\n"
"	int index = get_global_id(0);\n"
"	if(index >= numFluidParticles) return;\n"
"	\n"
"	if(retainValue[index])\n"
"	{\n"
"		int gridCellIndex = scanResults[index];\n"
"		b3FluidGridCombinedPos gridCellValue = valueIndexPairs[index].m_value;\n"
"		\n"
"		out_sortGridValues[gridCellIndex] = gridCellValue;\n"
"		\n"
"		//Perform a linear search for the lower range of this grid cell.\n"
"		//When r, the SPH interaction radius, is equivalent to the grid cell size, \n"
"		//the average number of particles per cell is frequently 4 to 7.\n"
"		int lowerParticleIndex = index;\n"
"		int upperParticleIndex = index;\n"
"		while( lowerParticleIndex > 0 && valueIndexPairs[lowerParticleIndex - 1].m_value == gridCellValue ) --lowerParticleIndex;\n"
"		\n"
"		out_iterators[gridCellIndex] = (b3FluidGridIterator){ lowerParticleIndex, upperParticleIndex };\n"
"	}\n"
"}\n"
"b3FluidGridCombinedPos getCombinedPosition_yAxisOriented(b3FluidGridPosition quantizedPosition)\n"
"{\n"
"	b3FluidGridCoordinate signedX = quantizedPosition.x + B3_FLUID_GRID_COORD_RANGE_HALVED;\n"
"	b3FluidGridCoordinate signedY = quantizedPosition.y + B3_FLUID_GRID_COORD_RANGE_HALVED;\n"
"	b3FluidGridCoordinate signedZ = quantizedPosition.z + B3_FLUID_GRID_COORD_RANGE_HALVED;\n"
"	\n"
"	b3FluidGridCombinedPos unsignedX = (b3FluidGridCombinedPos)signedX * B3_FLUID_GRID_COORD_RANGE;\n"
"	b3FluidGridCombinedPos unsignedY = (b3FluidGridCombinedPos)signedY;\n"
"	b3FluidGridCombinedPos unsignedZ = (b3FluidGridCombinedPos)signedZ * B3_FLUID_GRID_COORD_RANGE * B3_FLUID_GRID_COORD_RANGE;\n"
"	\n"
"	return unsignedX + unsignedY + unsignedZ;\n"
"}\n"
"b3FluidGridCombinedPos getCombinedPosition_zAxisOriented(b3FluidGridPosition quantizedPosition)\n"
"{\n"
"	b3FluidGridCoordinate signedX = quantizedPosition.x + B3_FLUID_GRID_COORD_RANGE_HALVED;\n"
"	b3FluidGridCoordinate signedY = quantizedPosition.y + B3_FLUID_GRID_COORD_RANGE_HALVED;\n"
"	b3FluidGridCoordinate signedZ = quantizedPosition.z + B3_FLUID_GRID_COORD_RANGE_HALVED;\n"
"	\n"
"	b3FluidGridCombinedPos unsignedX = (b3FluidGridCombinedPos)signedX * B3_FLUID_GRID_COORD_RANGE * B3_FLUID_GRID_COORD_RANGE;\n"
"	b3FluidGridCombinedPos unsignedY = (b3FluidGridCombinedPos)signedY * B3_FLUID_GRID_COORD_RANGE;\n"
"	b3FluidGridCombinedPos unsignedZ = (b3FluidGridCombinedPos)signedZ;\n"
"	\n"
"	return unsignedX + unsignedY + unsignedZ;\n"
"}\n"
"__kernel void convertCellValuesAndLoadCellIndex(__global b3FluidGridCombinedPos* activeCells, __global b3FluidGridValueIndexPair* yOrientedPairs, \n"
"								__global b3FluidGridValueIndexPair* zOrientedPairs, int numActiveCells)\n"
"{\n"
"	int index = get_global_id(0);\n"
"	if(index >= numActiveCells) return;\n"
"	\n"
"	b3FluidGridCombinedPos xAxisOrientedValue = activeCells[index];\n"
"	\n"
"	b3FluidGridPosition splitPosition;\n"
"	splitCombinedPosition(B3_FLUID_GRID_COORD_RANGE, B3_FLUID_GRID_COORD_RANGE, xAxisOrientedValue, \n"
"							&splitPosition.x, &splitPosition.y, &splitPosition.z);\n"
"	splitPosition.x -= B3_FLUID_GRID_COORD_RANGE_HALVED;\n"
"	splitPosition.y -= B3_FLUID_GRID_COORD_RANGE_HALVED;\n"
"	splitPosition.z -= B3_FLUID_GRID_COORD_RANGE_HALVED;\n"
"	\n"
"	yOrientedPairs[index].m_value = getCombinedPosition_yAxisOriented(splitPosition);\n"
"	yOrientedPairs[index].m_index = index;\n"
"	\n"
"	zOrientedPairs[index].m_value = getCombinedPosition_zAxisOriented(splitPosition);\n"
"	zOrientedPairs[index].m_index = index;\n"
"}\n"
"__kernel void writebackReorientedCellIndicies(__global b3FluidGridValueIndexPair* yOrientedPairs, __global b3FluidGridValueIndexPair* zOrientedPairs,\n"
"											__global int* yIndex, __global int* zIndex, int numActiveCells)\n"
"{\n"
"	int index = get_global_id(0);\n"
"	if(index >= numActiveCells) return;\n"
"	\n"
"	yIndex[ yOrientedPairs[index].m_index ] = index;\n"
"	zIndex[ zOrientedPairs[index].m_index ] = index;\n"
"}\n"
"__kernel void generateUniques(__global b3FluidGridValueIndexPair* sortedPairs, \n"
"							  __global b3FluidGridCombinedPos* out_activeCells, __global b3FluidGridIterator* out_cellContents,\n"
"							  __global int* out_numActiveCells, int numSortedPairs )\n"
"{\n"
"	//Assuming that out_activeCells[] is large enough to contain\n"
"	//all active cells( out_activeCells.size() >= numSortedPairs ).\n"
"	//Iterate from sortedPairs[0] to sortedPairs[numSortedPairs-1],\n"
"	//adding unique b3FluidGridCombinedPos(s) and b3FluidGridIterator(s) to \n"
"	//out_activeCells and out_cellContents, respectively.\n"
"	\n"
"	if( get_global_id(0) == 0 )\n"
"	{\n"
"		int numActiveCells = 0;\n"
"		\n"
"		if( numSortedPairs ) \n"
"		{\n"
"			//Crashes on compiling with Catalyst 13.1 if\n"
"			//(b3FluidGridIterator){INVALID_FIRST_INDEX, INVALID_FIRST_INDEX} is used directly\n"
"			int invalidLowerIndex = INVALID_FIRST_INDEX;\n"
"			int invalidUpperIndex = INVALID_LAST_INDEX;\n"
"		\n"
"			out_activeCells[numActiveCells] = sortedPairs[0].m_value;\n"
"			//out_cellContents[numActiveCells] = (b3FluidGridIterator){INVALID_FIRST_INDEX, INVALID_FIRST_INDEX};\n"
"			out_cellContents[numActiveCells] = (b3FluidGridIterator){invalidLowerIndex, invalidUpperIndex};\n"
"			++numActiveCells;\n"
"			\n"
"			out_cellContents[0].m_firstIndex = 0;\n"
"			out_cellContents[0].m_lastIndex = 0;\n"
"			\n"
"			for(int i = 1; i < numSortedPairs; ++i)\n"
"			{\n"
"				if( sortedPairs[i].m_value != sortedPairs[i - 1].m_value )\n"
"				{\n"
"					out_activeCells[numActiveCells] = sortedPairs[i].m_value;\n"
"					//out_cellContents[numActiveCells] = (b3FluidGridIterator){INVALID_FIRST_INDEX, INVALID_FIRST_INDEX};\n"
"					out_cellContents[numActiveCells] = (b3FluidGridIterator){invalidLowerIndex, invalidUpperIndex};\n"
"					++numActiveCells;\n"
"			\n"
"					int lastIndex = numActiveCells - 1;\n"
"					out_cellContents[lastIndex].m_firstIndex = i;\n"
"					out_cellContents[lastIndex].m_lastIndex = i;\n"
"					\n"
"					//\n"
"					out_cellContents[lastIndex - 1].m_lastIndex = i - 1;\n"
"				}\n"
"			}\n"
"			\n"
"			int valuesLastIndex = numSortedPairs - 1;\n"
"			if( sortedPairs[valuesLastIndex].m_value == sortedPairs[valuesLastIndex - 1].m_value )\n"
"			{\n"
"				int uniqueLastIndex = numActiveCells - 1;\n"
"				out_cellContents[uniqueLastIndex].m_lastIndex = valuesLastIndex;\n"
"			}\n"
"		}\n"
"		\n"
"		*out_numActiveCells = numActiveCells;\n"
"	}\n"
"}\n"
"inline void binaryRangeSearch(int numActiveCells, __global b3FluidGridCombinedPos* cellValues,\n"
"							  b3FluidGridCombinedPos lowerValue, b3FluidGridCombinedPos upperValue, int* out_lowerIndex, int* out_upperIndex)\n"
"{\n"
"	int first = 0;\n"
"	int last = numActiveCells - 1;\n"
"	\n"
"	while(first <= last)\n"
"	{\n"
"//#define USE_OPTIMIZED_BINARY_RANGE_SEARCH\n"
"#ifdef USE_OPTIMIZED_BINARY_RANGE_SEARCH\n"
"		int mid = (first + last) / 2;\n"
"		int lowerValueGreaterThanMidValue = (lowerValue > cellValues[mid]);\n"
"		int upperValueLesserThanMidValue = (upperValue < cellValues[mid]);\n"
"		\n"
"		first = (lowerValueGreaterThanMidValue) ? mid + 1 : first;\n"
"		last = (!lowerValueGreaterThanMidValue && upperValueLesserThanMidValue) ? last = mid - 1 : last;\n"
"		\n"
"		if( !lowerValueGreaterThanMidValue && !upperValueLesserThanMidValue )\n"
"		{\n"
"			int lowerIndex = mid;\n"
"			int upperIndex = mid;\n"
"			\n"
"			//Perform a linear search to find the lower and upper index range\n"
"			while(lowerIndex-1 >= 0 && cellValues[lowerIndex-1] >= lowerValue) lowerIndex--;\n"
"			while(upperIndex+1 < numActiveCells && cellValues[upperIndex+1] <= upperValue) upperIndex++;\n"
"			\n"
"			*out_lowerIndex = lowerIndex;\n"
"			*out_upperIndex = upperIndex;\n"
"			return;\n"
"		}\n"
"#else\n"
"		int mid = (first + last) / 2;\n"
"		if( lowerValue > cellValues[mid] )\n"
"		{\n"
"			first = mid + 1;\n"
"		}\n"
"		else if( upperValue < cellValues[mid] )\n"
"		{\n"
"			last = mid - 1;\n"
"		}\n"
"		else \n"
"		{\n"
"			//At this point, (lowerValue <= cellValues[mid] <= upperValue)\n"
"			//Perform a linear search to find the lower and upper index range\n"
"		\n"
"			int lowerIndex = mid;\n"
"			int upperIndex = mid;\n"
"			while(lowerIndex-1 >= 0 && cellValues[lowerIndex-1] >= lowerValue) lowerIndex--;\n"
"			while(upperIndex+1 < numActiveCells && cellValues[upperIndex+1] <= upperValue) upperIndex++;\n"
"		\n"
"			*out_lowerIndex = lowerIndex;\n"
"			*out_upperIndex = upperIndex;\n"
"			return;\n"
"		}\n"
"#endif\n"
"	}\n"
"	\n"
"	*out_lowerIndex = numActiveCells;\n"
"	*out_upperIndex = numActiveCells;\n"
"}\n"
"inline void findCellsFromGridPosition(int numActiveCells, __global b3FluidGridCombinedPos* cellValues, __global b3FluidGridIterator* cellContents, \n"
"										b3FluidGridPosition combinedPosition, b3FluidGridIterator* out_cells)\n"
"{\n"
"	b3FluidGridPosition cellIndicies[b3FluidSortingGrid_NUM_FOUND_CELLS_GPU];\n"
"	\n"
"	b3FluidGridPosition indicies = combinedPosition;\n"
"	for(int i = 0; i < b3FluidSortingGrid_NUM_FOUND_CELLS_GPU; ++i) cellIndicies[i] = indicies;\n"
"	cellIndicies[1].y++;\n"
"	cellIndicies[2].z++;\n"
"	cellIndicies[3].y++;\n"
"	cellIndicies[3].z++;\n"
"	\n"
"	cellIndicies[4].y--;\n"
"	cellIndicies[5].z--;\n"
"	cellIndicies[6].y--;\n"
"	cellIndicies[6].z--;\n"
"	\n"
"	cellIndicies[7].y++;\n"
"	cellIndicies[7].z--;\n"
"	\n"
"	cellIndicies[8].y--;\n"
"	cellIndicies[8].z++;\n"
"	\n"
"	for(int i = 0; i < b3FluidSortingGrid_NUM_FOUND_CELLS_GPU; ++i) \n"
"	{\n"
"		//Crashes on compiling with Catalyst 13.1 if\n"
"		//(b3FluidGridIterator){INVALID_FIRST_INDEX, INVALID_FIRST_INDEX} is used directly\n"
"		int invalidLowerIndex = INVALID_FIRST_INDEX;\n"
"		int invalidUpperIndex = INVALID_LAST_INDEX;\n"
"		out_cells[i] = (b3FluidGridIterator){invalidLowerIndex, invalidUpperIndex};\n"
"		//out_cells[i] = (b3FluidGridIterator){INVALID_FIRST_INDEX, INVALID_LAST_INDEX};\n"
"	}\n"
"	for(int i = 0; i < b3FluidSortingGrid_NUM_FOUND_CELLS_GPU; ++i)\n"
"	{\n"
"	\n"
"		b3FluidGridPosition lower = cellIndicies[i];\n"
"		lower.x--;\n"
"	\n"
"		b3FluidGridPosition upper = cellIndicies[i];\n"
"		upper.x++;\n"
"		\n"
"		int lowerIndex, upperIndex;\n"
"		binaryRangeSearch(numActiveCells, cellValues, getCombinedPosition(lower), getCombinedPosition(upper), &lowerIndex, &upperIndex);\n"
"		\n"
"		if(lowerIndex != numActiveCells)\n"
"		{\n"
"			out_cells[i] = (b3FluidGridIterator){cellContents[lowerIndex].m_firstIndex, cellContents[upperIndex].m_lastIndex};\n"
"		}\n"
"	\n"
"	}\n"
"}\n"
"__kernel void findNeighborCellsPerCell( __constant int* numActiveCells, __global b3FluidGridCombinedPos* cellValues, \n"
"										__global b3FluidGridIterator* cellContents, __global b3FluidSortingGridFoundCellsGpu* out_foundCells)\n"
"{\n"
"	int gridCellIndex = get_global_id(0);\n"
"	if(gridCellIndex >= *numActiveCells) return;\n"
"	\n"
"	b3FluidGridCombinedPos combinedPosition = cellValues[gridCellIndex];\n"
"	\n"
"	b3FluidGridPosition splitPosition;\n"
"	splitCombinedPosition(B3_FLUID_GRID_COORD_RANGE, B3_FLUID_GRID_COORD_RANGE, combinedPosition, \n"
"							&splitPosition.x, &splitPosition.y, &splitPosition.z);\n"
"	splitPosition.x -= B3_FLUID_GRID_COORD_RANGE_HALVED;\n"
"	splitPosition.y -= B3_FLUID_GRID_COORD_RANGE_HALVED;\n"
"	splitPosition.z -= B3_FLUID_GRID_COORD_RANGE_HALVED;\n"
"	b3FluidGridIterator foundCells[b3FluidSortingGrid_NUM_FOUND_CELLS_GPU];\n"
"	findCellsFromGridPosition(*numActiveCells, cellValues, cellContents, splitPosition, foundCells);\n"
"	for(int cell = 0; cell < b3FluidSortingGrid_NUM_FOUND_CELLS_GPU; ++cell) out_foundCells[gridCellIndex].m_iterators[cell] = foundCells[cell];\n"
"}\n"
"__kernel void findGridCellIndexPerParticle(__constant int* numActiveCells, __global b3FluidGridIterator* cellContents, \n"
"											__global int* out_gridCellIndicies)\n"
"{\n"
"	int gridCellIndex = get_global_id(0);\n"
"	if(gridCellIndex >= *numActiveCells) return;\n"
"	\n"
"	b3FluidGridIterator foundCell = cellContents[gridCellIndex];\n"
"	for(int n = foundCell.m_firstIndex; n <= foundCell.m_lastIndex; ++n) out_gridCellIndicies[n] = gridCellIndex;\n"
"}\n"
"//\n"
"#define B3_EPSILON FLT_EPSILON\n"
"__kernel void sphComputePressure(__constant b3FluidSphParametersGlobal* FG,  __constant b3FluidSphParametersLocal* FL,\n"
"								  __global b3Vector3* fluidPosition, __global b3Scalar* fluidDensity,\n"
"								  __global b3FluidSortingGridFoundCellsGpu* foundCells, __global int* foundCellIndex, int numFluidParticles)\n"
"{\n"
"	int i = get_global_id(0);\n"
"	if(i >= numFluidParticles) return;\n"
"	\n"
"	b3Scalar sum = FG->m_initialSum;\n"
"	\n"
"	for(int cell = 0; cell < b3FluidSortingGrid_NUM_FOUND_CELLS_GPU; ++cell) \n"
"	{\n"
"		b3FluidGridIterator foundCell = foundCells[ foundCellIndex[i] ].m_iterators[cell];\n"
"		\n"
"		for(int n = foundCell.m_firstIndex; n <= foundCell.m_lastIndex; ++n)\n"
"		{\n"
"			b3Vector3 delta = (fluidPosition[i] - fluidPosition[n]) * FG->m_simulationScale;	//Simulation scale distance\n"
"			b3Scalar distanceSquared = b3Vector3_length2(delta);\n"
"			\n"
"			b3Scalar c = FG->m_sphRadiusSquared - distanceSquared;\n"
"			sum += (c > 0.0f && i != n) ? c*c*c : 0.0f;		//If c is positive, the particle is within interaction radius(poly6 kernel radius)\n"
"		}\n"
"	}\n"
"	\n"
"	fluidDensity[i] = sum * FL->m_sphParticleMass * FG->m_poly6KernCoeff;\n"
"}\n"
"__kernel void sphComputeForce(__constant b3FluidSphParametersGlobal* FG, __constant b3FluidSphParametersLocal* FL,\n"
"							   __global b3Vector3* fluidPosition, __global b3Vector3* fluidVelEval, \n"
"							   __global b3Vector3* fluidSphForce, __global b3Scalar* fluidDensity,\n"
"							   __global b3FluidSortingGridFoundCellsGpu* foundCells, __global int* foundCellIndex, int numFluidParticles)\n"
"{\n"
"	b3Scalar vterm = FG->m_viscosityKernLapCoeff * FL->m_viscosity;\n"
"	\n"
"	int i = get_global_id(0);\n"
"	if(i >= numFluidParticles) return;\n"
"	\n"
"	b3Scalar density_i = fluidDensity[i];\n"
"	b3Scalar invDensity_i = 1.0f / density_i;\n"
"	b3Scalar pressure_i = (density_i - FL->m_restDensity) * FL->m_stiffness;\n"
"	\n"
"	b3Vector3 force = {0.0f, 0.0f, 0.0f, 0.0f};\n"
"	\n"
"	for(int cell = 0; cell < b3FluidSortingGrid_NUM_FOUND_CELLS_GPU; ++cell) \n"
"	{\n"
"		b3FluidGridIterator foundCell = foundCells[ foundCellIndex[i] ].m_iterators[cell];\n"
"		\n"
"		for(int n = foundCell.m_firstIndex; n <= foundCell.m_lastIndex; ++n)\n"
"		{	\n"
"			b3Vector3 delta = (fluidPosition[i] - fluidPosition[n]) * FG->m_simulationScale;	//Simulation scale distance\n"
"			b3Scalar distanceSquared = b3Vector3_length2(delta);\n"
"			\n"
"			if(FG->m_sphRadiusSquared > distanceSquared && i != n)\n"
"			{\n"
"				b3Scalar density_n = fluidDensity[n];\n"
"				b3Scalar invDensity_n = 1.0f / density_n;\n"
"				b3Scalar pressure_n = (density_n - FL->m_restDensity) * FL->m_stiffness;\n"
"			\n"
"				b3Scalar distance = sqrt(distanceSquared);\n"
"				b3Scalar c = FG->m_sphSmoothRadius - distance;\n"
"				b3Scalar pterm = -0.5f * c * FG->m_spikyKernGradCoeff * (pressure_i + pressure_n);\n"
"				pterm /= (distance < B3_EPSILON) ? B3_EPSILON : distance;\n"
"				\n"
"				b3Scalar dterm = c * invDensity_i * invDensity_n;\n"
"				\n"
"				force += (delta * pterm + (fluidVelEval[n] - fluidVelEval[i]) * vterm) * dterm;\n"
"			}\n"
"		}\n"
"	}\n"
"	\n"
"	fluidSphForce[i] = force * FL->m_sphParticleMass;\n"
"}\n"
"__kernel void applyForces(__constant b3FluidSphParametersGlobal* FG,  __constant b3FluidSphParametersLocal* FL, \n"
"						__global b3Vector3* fluidExternalForce, __global b3Vector3* fluidSphAcceleration,\n"
"						__global b3Vector3* fluidVel, __global b3Vector3* fluidVelEval, int numFluidParticles)\n"
"{\n"
"	int i = get_global_id(0);\n"
"	if(i >= numFluidParticles) return;\n"
"	\n"
"	b3Vector3 sphAcceleration = fluidSphAcceleration[i];\n"
"	{\n"
"		b3Scalar accelMagnitude = sqrt( b3Vector3_length2(sphAcceleration) );\n"
"		\n"
"		b3Scalar simulationScaleAccelLimit = FL->m_sphAccelLimit * FG->m_simulationScale;\n"
"		if(accelMagnitude > simulationScaleAccelLimit) sphAcceleration *= simulationScaleAccelLimit / accelMagnitude;\n"
"	}\n"
"	b3Vector3 acceleration = FL->m_gravity + sphAcceleration + fluidExternalForce[i] / FL->m_particleMass;\n"
"	\n"
"	b3Vector3 vel = fluidVel[i];\n"
"	\n"
"	b3Vector3 vnext = vel + acceleration * FG->m_timeStep;		//v(t+1/2) = v(t-1/2) + a(t) dt	\n"
"	fluidVel[i] = vnext;\n"
"	\n"
"	fluidExternalForce[i] = (b3Vector3){0.0f, 0.0f, 0.0f, 0.0f};\n"
"}\n"
"inline void resolveAabbCollision_impulse(__constant b3FluidSphParametersGlobal* FG,  __constant b3FluidSphParametersLocal* FL, \n"
"										b3Vector3 velocity, b3Vector3 normal, b3Scalar distance, b3Vector3* out_impulse)\n"
"{\n"
"	if( distance < 0.0f )	//Negative distance indicates penetration\n"
"	{\n"
"		b3Scalar penetratingMagnitude = b3Vector3_dot(velocity, -normal);\n"
"		if( penetratingMagnitude < 0.0f ) penetratingMagnitude = 0.0f;\n"
"		\n"
"		b3Vector3 penetratingVelocity = -normal * penetratingMagnitude;\n"
"		b3Vector3 tangentialVelocity = velocity - penetratingVelocity;\n"
"		\n"
"		penetratingVelocity *= 1.0f + FL->m_boundaryRestitution;\n"
"		\n"
"		b3Scalar positionError = (-distance) * (FG->m_simulationScale/FG->m_timeStep) * FL->m_boundaryErp;\n"
"		\n"
"		*out_impulse += -( penetratingVelocity + (-normal*positionError) + tangentialVelocity * FL->m_boundaryFriction );\n"
"	}\n"
"}\n"
"inline void accumulateBoundaryImpulse(__constant b3FluidSphParametersGlobal* FG,  __constant b3FluidSphParametersLocal* FL, \n"
"								b3Scalar simScaleParticleRadius, b3Vector3 pos, b3Vector3 vel, b3Vector3* out_impulse)\n"
"{\n"
"	b3Scalar radius = simScaleParticleRadius;\n"
"	b3Scalar simScale = FG->m_simulationScale;\n"
"	\n"
"	b3Vector3 boundaryMin = FL->m_aabbBoundaryMin;\n"
"	b3Vector3 boundaryMax = FL->m_aabbBoundaryMax;\n"
"	\n"
"	resolveAabbCollision_impulse( FG, FL, vel, (b3Vector3){ 1.0f, 0.0f, 0.0f, 0.0f}, ( pos.x - boundaryMin.x )*simScale - radius, out_impulse );\n"
"	resolveAabbCollision_impulse( FG, FL, vel, (b3Vector3){-1.0f, 0.0f, 0.0f, 0.0f}, ( boundaryMax.x - pos.x )*simScale - radius, out_impulse );\n"
"	resolveAabbCollision_impulse( FG, FL, vel, (b3Vector3){0.0f,  1.0f, 0.0f, 0.0f}, ( pos.y - boundaryMin.y )*simScale - radius, out_impulse );\n"
"	resolveAabbCollision_impulse( FG, FL, vel, (b3Vector3){0.0f, -1.0f, 0.0f, 0.0f}, ( boundaryMax.y - pos.y )*simScale - radius, out_impulse );\n"
"	resolveAabbCollision_impulse( FG, FL, vel, (b3Vector3){0.0f, 0.0f,  1.0f, 0.0f}, ( pos.z - boundaryMin.z )*simScale - radius, out_impulse );\n"
"	resolveAabbCollision_impulse( FG, FL, vel, (b3Vector3){0.0f, 0.0f, -1.0f, 0.0f}, ( boundaryMax.z - pos.z )*simScale - radius, out_impulse );\n"
"}\n"
"__kernel void collideAabbImpulse(__constant b3FluidSphParametersGlobal* FG,  __constant b3FluidSphParametersLocal* FL, \n"
"								__global b3Vector3* fluidPosition, __global b3Vector3* fluidVel, __global b3Vector3* fluidVelEval, \n"
"								int numFluidParticles)\n"
"{\n"
"	int i = get_global_id(0);\n"
"	if(i >= numFluidParticles) return;\n"
"	\n"
"	b3Vector3 pos = fluidPosition[i];\n"
"	b3Vector3 vel = fluidVel[i];\n"
"	\n"
"	b3Scalar simScaleParticleRadius = FL->m_particleRadius * FG->m_simulationScale;\n"
"	\n"
"	b3Vector3 aabbImpulse = (b3Vector3){0.0f, 0.0f, 0.0f, 0.0f};\n"
"	accumulateBoundaryImpulse(FG, FL, simScaleParticleRadius, pos, vel, &aabbImpulse);\n"
"	\n"
"	//Leapfrog integration\n"
"	b3Vector3 vnext = vel + aabbImpulse;\n"
"	fluidVel[i] = vnext;\n"
"}\n"
"__kernel void integratePositions(__constant b3FluidSphParametersGlobal* FG, __constant b3FluidSphParametersLocal* FL, \n"
"								__global b3Vector3* fluidPosition, __global b3Vector3* fluidVel, __global b3Vector3* fluidVelEval, \n"
"								int numFluidParticles)\n"
"{\n"
"	int i = get_global_id(0);\n"
"	if(i >= numFluidParticles) return;\n"
"	\n"
"	b3Scalar timeStepDivSimScale = FG->m_timeStep / FG->m_simulationScale;\n"
"	\n"
"	b3Vector3 prevVelocity = fluidVelEval[i];	//Velocity at (t-1/2)\n"
"	b3Vector3 nextVelocity = fluidVel[i];		//Velocity at (t+1/2)\n"
"	\n"
"	if(FL->m_speedLimit != 0.0f)\n"
"	{\n"
"		b3Scalar simulationScaleSpeedLimit = FL->m_speedLimit * FG->m_simulationScale;\n"
"	\n"
"		b3Scalar speed = sqrt( b3Vector3_length2(nextVelocity) );\n"
"		if(speed > simulationScaleSpeedLimit) \n"
"		{\n"
"			nextVelocity *= simulationScaleSpeedLimit / speed;\n"
"			\n"
"			fluidVelEval[i] = (prevVelocity + nextVelocity) * 0.5f;		//v(t+1) = [v(t-1/2) + v(t+1/2)] * 0.5		used to compute (sph)forces later\n"
"			fluidVel[i] = nextVelocity;\n"
"		}\n"
"	}\n"
"	\n"
"	//Leapfrog integration\n"
"	//p(t+1) = p(t) + v(t+1/2)*dt\n"
"	fluidPosition[i] += nextVelocity * timeStepDivSimScale;\n"
"}\n"
"// ////////////////////////////////////////////////////////////////////////////\n"
"// Modulo Hash Grid\n"
"// ////////////////////////////////////////////////////////////////////////////\n"
"#define B3_FLUID_HASH_GRID_COORD_RANGE 64\n"
"b3FluidGridCombinedPos getCombinedPositionModulo(b3FluidGridPosition quantizedPosition)\n"
"{\n"
"	//as_uint() requires that sizeof(b3FluidGridCombinedPos) == sizeof(b3FluidGridCoordinate)\n"
"	//This presents an issue if B3_ENABLE_FLUID_SORTING_GRID_LARGE_WORLD_SUPPORT is #defined\n"
"	b3FluidGridCombinedPos unsignedX = as_uint(quantizedPosition.x) % B3_FLUID_HASH_GRID_COORD_RANGE;\n"
"	b3FluidGridCombinedPos unsignedY = as_uint(quantizedPosition.y) % B3_FLUID_HASH_GRID_COORD_RANGE;\n"
"	b3FluidGridCombinedPos unsignedZ = as_uint(quantizedPosition.z) % B3_FLUID_HASH_GRID_COORD_RANGE;\n"
"	\n"
"	return unsignedX \n"
"		+ unsignedY * B3_FLUID_HASH_GRID_COORD_RANGE\n"
"		+ unsignedZ * B3_FLUID_HASH_GRID_COORD_RANGE* B3_FLUID_HASH_GRID_COORD_RANGE;\n"
"}\n"
"__kernel void generateValueIndexPairsModulo(__global b3Vector3* fluidPositions, __global b3FluidGridValueIndexPair* out_pairs, \n"
"										b3Scalar cellSize, int numFluidParticles)\n"
"{\n"
"	int index = get_global_id(0);\n"
"	if(index >= numFluidParticles) return;\n"
"	\n"
"	b3FluidGridValueIndexPair result;\n"
"	result.m_index = index;\n"
"	result.m_value = getCombinedPositionModulo( getDiscretePosition(cellSize, fluidPositions[index]) );\n"
"	\n"
"	out_pairs[index] = result;\n"
"}\n"
"__kernel void resetGridCellsModulo(__global b3FluidGridIterator* out_iterators, int numGridCells)\n"
"{\n"
"	int index = get_global_id(0);\n"
"	if(index >= numGridCells) return;\n"
"	\n"
"	//Crashes on compiling with Catalyst 13.1 if\n"
"	//(b3FluidGridIterator){INVALID_FIRST_INDEX, INVALID_FIRST_INDEX} is used directly\n"
"	int invalidLowerIndex = INVALID_FIRST_INDEX;\n"
"	int invalidUpperIndex = INVALID_LAST_INDEX;\n"
"	out_iterators[index] = (b3FluidGridIterator){invalidLowerIndex, invalidUpperIndex};\n"
"	//out_iterators[index] = (b3FluidGridIterator){INVALID_FIRST_INDEX, INVALID_FIRST_INDEX};\n"
"}\n"
"__kernel void detectIndexRangesModulo(__global b3Vector3* fluidPosition, __global b3FluidGridValueIndexPair* valueIndexPairs, \n"
"								__global b3FluidGridIterator* out_iterators, b3Scalar gridCellSize, int numFluidParticles)\n"
"{\n"
"	int index = get_global_id(0);\n"
"	if(index >= numFluidParticles) return;\n"
"	\n"
"	b3FluidGridCombinedPos gridCellValue = valueIndexPairs[index].m_value;\n"
"	\n"
"	int lastValidIndex = numFluidParticles - 1;\n"
"	\n"
"	//if the next particle has a different b3FluidGridCombinedPos(is in another cell),\n"
"	//then this particle has the highest index in its cell\n"
"	int isLastParticleInCell = (index < lastValidIndex) ? (gridCellValue != valueIndexPairs[index+1].m_value) : 1;\n"
"	\n"
"	if(isLastParticleInCell)\n"
"	{\n"
"		int lowerParticleIndex = index;\n"
"		int upperParticleIndex = index;\n"
"		while( lowerParticleIndex > 0 && valueIndexPairs[lowerParticleIndex - 1].m_value == gridCellValue ) --lowerParticleIndex;\n"
"		\n"
"		int gridCellIndex = getCombinedPositionModulo( getDiscretePosition(gridCellSize, fluidPosition[index]) );\n"
"		out_iterators[gridCellIndex] = (b3FluidGridIterator){ lowerParticleIndex, upperParticleIndex };\n"
"	}\n"
"}\n"
"__kernel void sphComputePressureModulo(__constant b3FluidSphParametersGlobal* FG,  __constant b3FluidSphParametersLocal* FL,\n"
"								__global b3Vector3* fluidPosition, __global b3Scalar* fluidDensity,\n"
"								__global b3FluidGridIterator* cellContents, b3Scalar gridCellSize, int numFluidParticles)\n"
"{\n"
"	int i = get_global_id(0);\n"
"	if(i >= numFluidParticles) return;\n"
"	\n"
"	b3Scalar sum = FG->m_initialSum;\n"
"	\n"
"	b3FluidGridPosition centerCell = getDiscretePosition(gridCellSize, fluidPosition[i]);\n"
"	centerCell.x--;\n"
"	centerCell.y--;\n"
"	centerCell.z--;\n"
"	\n"
"	for(b3FluidGridCoordinate offsetZ = 0; offsetZ < 3; ++offsetZ)\n"
"		for(b3FluidGridCoordinate offsetY = 0; offsetY < 3; ++offsetY)\n"
"			for(b3FluidGridCoordinate offsetX = 0; offsetX < 3; ++offsetX)\n"
"			{\n"
"				b3FluidGridPosition currentCell = centerCell;\n"
"				currentCell.z += offsetZ;\n"
"				currentCell.y += offsetY;\n"
"				currentCell.x += offsetX;\n"
"			\n"
"				int gridCellIndex = getCombinedPositionModulo(currentCell);\n"
"				b3FluidGridIterator gridCell = cellContents[gridCellIndex];\n"
"				\n"
"				for(int n = gridCell.m_firstIndex; n <= gridCell.m_lastIndex; ++n)\n"
"				{\n"
"					b3Vector3 delta = (fluidPosition[i] - fluidPosition[n]) * FG->m_simulationScale;	//Simulation scale distance\n"
"					b3Scalar distanceSquared = b3Vector3_length2(delta);\n"
"					\n"
"					b3Scalar c = FG->m_sphRadiusSquared - distanceSquared;\n"
"					sum += (c > 0.0f && i != n) ? c*c*c : 0.0f;		//If c is positive, the particle is within interaction radius(poly6 kernel radius)\n"
"				}\n"
"			}\n"
"	\n"
"	fluidDensity[i] = sum * FL->m_sphParticleMass * FG->m_poly6KernCoeff;\n"
"}\n"
"__kernel void sphComputeForceModulo(__constant b3FluidSphParametersGlobal* FG, __constant b3FluidSphParametersLocal* FL,\n"
"							__global b3Vector3* fluidPosition, __global b3Vector3* fluidVelEval, \n"
"							__global b3Vector3* fluidSphForce, __global b3Scalar* fluidDensity,\n"
"							__global b3FluidGridIterator* cellContents, b3Scalar gridCellSize, int numFluidParticles)\n"
"{\n"
"	b3Scalar vterm = FG->m_viscosityKernLapCoeff * FL->m_viscosity;\n"
"	\n"
"	int i = get_global_id(0);\n"
"	if(i >= numFluidParticles) return;\n"
"	\n"
"	b3Scalar density_i = fluidDensity[i];\n"
"	b3Scalar invDensity_i = 1.0f / density_i;\n"
"	b3Scalar pressure_i = (density_i - FL->m_restDensity) * FL->m_stiffness;\n"
"	\n"
"	b3Vector3 force = {0.0f, 0.0f, 0.0f, 0.0f};\n"
"	\n"
"	b3FluidGridPosition centerCell = getDiscretePosition(gridCellSize, fluidPosition[i]);\n"
"	centerCell.x--;\n"
"	centerCell.y--;\n"
"	centerCell.z--;\n"
"	\n"
"	for(b3FluidGridCoordinate offsetZ = 0; offsetZ < 3; ++offsetZ)\n"
"		for(b3FluidGridCoordinate offsetY = 0; offsetY < 3; ++offsetY)\n"
"			for(b3FluidGridCoordinate offsetX = 0; offsetX < 3; ++offsetX)\n"
"			{\n"
"				b3FluidGridPosition currentCell = centerCell;\n"
"				currentCell.z += offsetZ;\n"
"				currentCell.y += offsetY;\n"
"				currentCell.x += offsetX;\n"
"				\n"
"				int gridCellIndex = getCombinedPositionModulo(currentCell);\n"
"				b3FluidGridIterator gridCell = cellContents[gridCellIndex];\n"
"				\n"
"				for(int n = gridCell.m_firstIndex; n <= gridCell.m_lastIndex; ++n)\n"
"				{	\n"
"					b3Vector3 delta = (fluidPosition[i] - fluidPosition[n]) * FG->m_simulationScale;	//Simulation scale distance\n"
"					b3Scalar distanceSquared = b3Vector3_length2(delta);\n"
"					\n"
"					if(FG->m_sphRadiusSquared > distanceSquared && i != n)\n"
"					{\n"
"						b3Scalar density_n = fluidDensity[n];\n"
"						b3Scalar invDensity_n = 1.0f / density_n;\n"
"						b3Scalar pressure_n = (density_n - FL->m_restDensity) * FL->m_stiffness;\n"
"					\n"
"						b3Scalar distance = sqrt(distanceSquared);\n"
"						b3Scalar c = FG->m_sphSmoothRadius - distance;\n"
"						b3Scalar pterm = -0.5f * c * FG->m_spikyKernGradCoeff * (pressure_i + pressure_n);\n"
"						pterm /= (distance < B3_EPSILON) ? B3_EPSILON : distance;\n"
"						\n"
"						b3Scalar dterm = c * invDensity_i * invDensity_n;\n"
"						\n"
"						force += (delta * pterm + (fluidVelEval[n] - fluidVelEval[i]) * vterm) * dterm;\n"
"					}\n"
"				}\n"
"			}\n"
"	\n"
"	fluidSphForce[i] = force * FL->m_sphParticleMass;\n"
"}\n"
;