add_subdirectory(union-api)
add_subdirectory(gothic-api)

# union
add_library(union INTERFACE)

target_include_directories(union INTERFACE "gothic-userapi/")

target_link_libraries(union
	INTERFACE
		gothic_api
		union_api_lib
)