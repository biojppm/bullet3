#ifndef GPU_DEMO_H
#define GPU_DEMO_H
class GLInstancingRenderer;




class GpuDemo
{
protected:
	
	struct GpuDemoInternalData*	m_clData;

	
	virtual void initCL(int preferredDeviceIndex, int preferredPlatformIndex);
	virtual void exitCL();
public:
	
	typedef class GpuDemo* (CreateFunc)();

	struct ConstructionInfo
    {
            bool useOpenCL;
            int preferredOpenCLPlatformIndex;
            int preferredOpenCLDeviceIndex;
            int arraySizeX;
            int arraySizeY;
            int arraySizeZ;
            bool m_useConcaveMesh;
            float gapX;
            float gapY;
            float gapZ;
            GLInstancingRenderer*   m_instancingRenderer;
			class b3gWindowInterface*	m_window;
			class GwenUserInterface*	m_gui;

            ConstructionInfo()
                    :useOpenCL(true),
                    preferredOpenCLPlatformIndex(-1),
                    preferredOpenCLDeviceIndex(-1),
					arraySizeX(20),
		arraySizeY(20),
		arraySizeZ(20),
		m_useConcaveMesh(false),
		gapX(14.3),
		gapY(14.0),
		gapZ(14.3),
                    m_instancingRenderer(0),
					m_window(0),
					m_gui(0)
            {
            }
    };

	GpuDemo();
	virtual ~GpuDemo();
	
	virtual const char* getName()=0;
	
	virtual void    initPhysics(const ConstructionInfo& ci)=0;
	
	virtual void    exitPhysics()=0;
	
	virtual void renderScene()=0;
	
	virtual void clientMoveAndDisplay()=0;

	virtual void resize(int width, int height) {}
	
	int	registerGraphicsSphereShape(const ConstructionInfo& ci, float radius, bool usePointSprites=true, int largeSphereThreshold=100, int mediumSphereThreshold=10);

};

#endif

