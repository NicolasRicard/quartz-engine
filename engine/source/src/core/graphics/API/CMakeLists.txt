add_subdirectory(gl)

set(currentDir ${CMAKE_CURRENT_LIST_DIR})
set(apiSources
	${currentDir}/Context.cpp
	${currentDir}/IStateManager.cpp
	${currentDir}/IBuffer.cpp
	${currentDir}/BufferLayout.cpp
	${currentDir}/ITexture.cpp
	${currentDir}/ITextureArray.cpp
	${currentDir}/IFramebuffer.cpp
	${currentDir}/IShaderPipeline.cpp

	${glAPISources}

	PARENT_SCOPE
)
