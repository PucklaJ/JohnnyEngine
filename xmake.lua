set_project("johnny-engine")

add_repositories("box2d_xmake https://github.com/PucklaMotzer09/xmake-repo.git box2d_xmake")
add_requires("glew", "libsdl", "libsdl_ttf", "libsdl_mixer", "libsdl_gfx", "box2d", "assimp", "stb", "tmxparser")

add_rules("mode.debug", "mode.release")
target("johnny-engine")
    set_kind("static")
    if is_os("windows") then
        add_cxxflags("/EHsc")
    end
    add_defines("STB_IMAGE_IMPLEMENTATION")

    add_packages("glew", "libsdl", "libsdl_ttf", "libsdl_mixer", "libsdl_gfx", "box2d", "assimp", "stb", "tmxparser")

    add_files("src/*.cpp")
    add_headerfiles("include/*.h")
    add_includedirs("include")

target("johnny-engine-template")
    set_kind("binary")
    if is_os("windows") then
        add_cxxflags("/EHsc")
        add_defines("SDL_MAIN_HANDLED")
    end

    add_deps("johnny-engine")
    add_packages("glew", "libsdl", "libsdl_ttf", "libsdl_mixer", "libsdl_gfx", "box2d", "assimp", "stb", "tmxparser")

    add_files("TemplateProject/*.cpp")
    add_headerfiles("TemplateProject/*.h")
    add_includedirs("include")