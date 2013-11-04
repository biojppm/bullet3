//this file is autogenerated using stringify.bat (premake --stringify) in the build folder of this project
static const char* fluidSphCL2= \
"/*\n"
"Bullet-FLUIDS \n"
"Copyright (c) 2012 Jackson Lee\n"
"\n"
"This software is provided 'as-is', without any express or implied warranty.\n"
"In no event will the authors be held liable for any damages arising from the use of this software.\n"
"Permission is granted to anyone to use this software for any purpose, \n"
"including commercial applications, and to alter it and redistribute it freely, \n"
"subject to the following restrictions:\n"
"\n"
"1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.\n"
"2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.\n"
"3. This notice may not be removed or altered from any source distribution.\n"
"*/\n"
"\n"
"#ifdef cl_amd_printf\n"
"	#pragma OPENCL EXTENSION cl_amd_printf : enable\n"
"#endif\n"
"\n"
"typedef float b3Scalar;\n"
"typedef float4 b3Vector3;\n"
"#define b3Max max\n"
"#define b3Min min\n"
"\n"
"\n"
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
"\n"
"\n"
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
"\n"
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
"\n"
"\n"
"typedef unsigned int b3FluidGridCombinedPos;\n"
"typedef int b3FluidGridCoordinate;\n"
"\n"
"typedef struct\n"
"{\n"
"	int m_firstIndex;\n"
"	int m_lastIndex;\n"
"	\n"
"} b3FluidGridIterator;\n"
"\n"
"typedef struct \n"
"{\n"
"	b3FluidGridCombinedPos m_value;\n"
"	int m_index;\n"
"	\n"
"} b3FluidGridValueIndexPair;\n"
"\n"
"typedef struct\n"
"{\n"
"	b3FluidGridCoordinate x;		\n"
"	b3FluidGridCoordinate y;\n"
"	b3FluidGridCoordinate z;\n"
"	b3FluidGridCoordinate padding;\n"
"	\n"
"} b3FluidGridPosition;\n"
"\n"
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
"\n"
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
"\n"
"__kernel void generateValueIndexPairs(__global b3Vector3* fluidPositions, __global b3FluidGridValueIndexPair* out_pairs, \n"
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
"\n"
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
"\n"
"\n"
"__kernel void resetGridCells(__global b3FluidGridIterator* out_iterators, int numGridCells)\n"
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
"__kernel void detectIndexRanges(__global b3Vector3* fluidPosition, __global b3FluidGridValueIndexPair* valueIndexPairs, \n"
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
"\n"
"\n"
"//\n"
"#define B3_EPSILON FLT_EPSILON\n"
"__kernel void sphComputePressure(__constant b3FluidSphParametersGlobal* FG,  __constant b3FluidSphParametersLocal* FL,\n"
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
"\n"
"\n"
"__kernel void sphComputeForce(__constant b3FluidSphParametersGlobal* FG, __constant b3FluidSphParametersLocal* FL,\n"
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
"\n"
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
"\n"
"	b3Vector3 acceleration = FL->m_gravity + sphAcceleration + fluidExternalForce[i] / FL->m_particleMass;\n"
"	\n"
"	b3Vector3 vel = fluidVel[i];\n"
"	\n"
"	b3Vector3 vnext = vel + acceleration * FG->m_timeStep;		//v(t+1/2) = v(t-1/2) + a(t) dt	\n"
"	fluidVel[i] = vnext;\n"
"	\n"
"	fluidExternalForce[i] = (b3Vector3){0.0f, 0.0f, 0.0f, 0.0f};\n"
"}\n"
"\n"
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
"\n"
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
"\n"
"\n"
;
