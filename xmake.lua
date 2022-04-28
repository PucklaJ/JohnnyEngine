set_project("johnny-engine")

add_requires("glew", "libsdl", "libsdl_ttf", "libsdl_mixer", "libsdl_gfx", "box2d", "assimp", "stb", "tmxparser")

add_rules("mode.debug", "mode.release")
target("johnny-engine")
    set_kind("$(kind)")
    if is_os("windows") then
        add_cxxflags("/EHsc")
    end
    add_defines("STB_IMAGE_IMPLEMENTATION")
    set_languages("c++11")

    add_packages("glew", "libsdl", "libsdl_ttf", "libsdl_mixer", "libsdl_gfx", "box2d", "assimp", "stb", "tmxparser")

    add_files("src/*.cpp")
    add_headerfiles("include/*.h")
    add_includedirs("include")
