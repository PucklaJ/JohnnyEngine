set_project("johnny-engine-template")

add_requires("johnnyengine")

add_rules("mode.debug", "mode.release")
target("johnny-engine-template")
    set_kind("binary")
    if is_os("windows") then
        add_cxxflags("/EHsc")
        add_defines("SDL_MAIN_HANDLED")
    end

    add_packages("johnnyengine")

    add_files("*.cpp")
    add_headerfiles("*.h")