set_project("johnny-engine")

add_rules("mode.debug", "mode.release")
target("johnny-engine")
    set_kind("static")
    if is_os("windows") then
        add_cxxflags("/EHsc")
    end

    add_files("src/*.cpp")
    add_headerfiles("include/*.h")