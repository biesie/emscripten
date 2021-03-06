#MiniCL provides a small subset of OpenCL

INCLUDE_DIRECTORIES(
	${BULLET_PHYSICS_SOURCE_DIR}/src
	${VECTOR_MATH_INCLUDE}
)

ADD_LIBRARY(MiniCL
		MiniCL.cpp
		MiniCLTaskScheduler.cpp
		MiniCLTaskScheduler.h
		MiniCLTask/MiniCLTask.cpp
		MiniCLTask/MiniCLTask.h
		../MiniCL/cl.h
		../MiniCL/cl_gl.h
		../MiniCL/cl_platform.h
		../MiniCL/cl_MiniCL_Defs.h
)
SET_TARGET_PROPERTIES(MiniCL PROPERTIES VERSION ${BULLET_VERSION})
SET_TARGET_PROPERTIES(MiniCL PROPERTIES SOVERSION ${BULLET_VERSION})


IF (BUILD_SHARED_LIBS)
	TARGET_LINK_LIBRARIES(MiniCL BulletMultiThreaded BulletDynamics BulletCollision)
ENDIF (BUILD_SHARED_LIBS)

IF (INSTALL_LIBS)
	IF (NOT INTERNAL_CREATE_DISTRIBUTABLE_MSVC_PROJECTFILES)
		#INSTALL of other files requires CMake 2.6
		IF (${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION} GREATER 2.5)
#			IF(INSTALL_EXTRA_LIBS)
				IF (APPLE AND BUILD_SHARED_LIBS AND FRAMEWORK)
					INSTALL(TARGETS MiniCL DESTINATION .)
				ELSE (APPLE AND BUILD_SHARED_LIBS AND FRAMEWORK)
				INSTALL(TARGETS MiniCL DESTINATION lib${LIB_SUFFIX})
					INSTALL(DIRECTORY
${CMAKE_CURRENT_SOURCE_DIR} DESTINATION ${INCLUDE_INSTALL_DIR} FILES_MATCHING
PATTERN "*.h"  PATTERN ".svn" EXCLUDE PATTERN "CMakeFiles" EXCLUDE)
				ENDIF (APPLE AND BUILD_SHARED_LIBS AND FRAMEWORK)
#			ENDIF (INSTALL_EXTRA_LIBS)
		ENDIF (${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION} GREATER 2.5)
	ENDIF (NOT INTERNAL_CREATE_DISTRIBUTABLE_MSVC_PROJECTFILES)
ENDIF (INSTALL_LIBS)

