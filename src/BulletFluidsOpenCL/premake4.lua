function createProject(vendor)
	hasCL = findOpenCL(vendor)
	
	if (hasCL) then
		
		project ("BulletFluidsOpenCL_" .. vendor)
	
		initOpenCL(vendor)
			
		kind "StaticLib"
		
		targetdir "../../lib"
		includedirs {
			".",".."
		}
		
		files {
			"**.cpp",
			"**.h"
		}
		
	end
end

createProject("AMD")
createProject("Intel")
createProject("NVIDIA")
createProject("Apple")