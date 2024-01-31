# union-api

file(GLOB_RECURSE SRC
	"union-api/*.cpp"
)

add_library(union-api STATIC)
target_sources(union-api PRIVATE ${SRC})

set_target_properties(union-api PROPERTIES
        OUTPUT_NAME "UnionApi"
)

target_compile_definitions(union-api
	PUBLIC
		_UNION_API_LIB
	PRIVATE
		_UNION_API_BUILD
)

target_include_directories(union-api PUBLIC "union-api/union-api")
target_link_directories(union-api PUBLIC "union-api/union-api")

# gothic-api

file(
	COPY "gothic-api/"
	DESTINATION "${CMAKE_CURRENT_BINARY_DIR}"
	PATTERN "ZenGin/Gothic_UserAPI" EXCLUDE
)

add_library(gothic-api INTERFACE)
target_sources(gothic-api
	INTERFACE
		"${CMAKE_CURRENT_BINARY_DIR}/ZenGin/zGothicAPI.cpp"
)

target_include_directories(gothic-api INTERFACE "${CMAKE_CURRENT_BINARY_DIR}")
target_link_directories(gothic-api INTERFACE "${CMAKE_CURRENT_BINARY_DIR}")

# gothic-userapi

add_custom_target(gothic-userapi
	COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/gothic-userapi" "${CMAKE_CURRENT_BINARY_DIR}/ZenGin/Gothic_UserAPI"
)

# union

add_library(union INTERFACE)

target_link_libraries(union INTERFACE gothic-api union-api)
add_dependencies(union gothic-userapi)