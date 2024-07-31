add_subdirectory(union-api)

set(GOTHIC_API_G1 OFF)
set(GOTHIC_API_G1A OFF)
set(GOTHIC_API_G2 OFF)
set(GOTHIC_API_G2A ON)

add_subdirectory(gothic-api)

# union
add_library(union INTERFACE)

target_include_directories(union INTERFACE "gothic-userapi/")

target_link_libraries(union
	INTERFACE
		gothic_api
		union_api_lib
)