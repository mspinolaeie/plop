cmake_minimum_required(VERSION 3.21)

project(plop LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

option(PLOP_BUILD_QT_GUI "Build the Qt Widgets GUI" ON)

set(PLOP_CORE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/plop_src/plop_xe10")
set(PLOP_Z88_DIR "${CMAKE_CURRENT_SOURCE_DIR}/plop_src/z88src/z88mix12")
set(PLOP_GUI_DIR "${CMAKE_CURRENT_SOURCE_DIR}/qt_gui")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

set(PLOP_CORE_SOURCES
  "${PLOP_CORE_DIR}/grid_gen.cpp"
  "${PLOP_CORE_DIR}/plate.cpp"
  "${PLOP_CORE_DIR}/plate_global.cpp"
  "${PLOP_CORE_DIR}/plop_debug.cpp"
  "${PLOP_CORE_DIR}/plop_parser.cpp"
  "${PLOP_CORE_DIR}/plop_run.cpp"
  "${PLOP_CORE_DIR}/plot.cpp"
  "${PLOP_CORE_DIR}/sparsemat.cpp"
)

add_library(plop_core STATIC ${PLOP_CORE_SOURCES})
target_include_directories(plop_core PUBLIC "${PLOP_CORE_DIR}")
target_compile_definitions(plop_core PUBLIC use_sparse)
if(MINGW)
  target_link_libraries(plop_core PUBLIC m)
endif()

add_executable(plop_cli
  "${PLOP_CORE_DIR}/plop_main.cpp"
  "${PLOP_CORE_DIR}/plop_cli_runtime.cpp"
)
target_link_libraries(plop_cli PRIVATE plop_core)
set_target_properties(plop_cli PROPERTIES OUTPUT_NAME plop_cli)

set(PLOP_Z88I1_SOURCES
  "${PLOP_Z88_DIR}/ale88i.c"
  "${PLOP_Z88_DIR}/dyn88i1.c"
  "${PLOP_Z88_DIR}/lan88i1.c"
  "${PLOP_Z88_DIR}/ri188i.c"
  "${PLOP_Z88_DIR}/w4y88i.c"
  "${PLOP_Z88_DIR}/wlog88i1.c"
  "${PLOP_Z88_DIR}/wria88i.c"
  "${PLOP_Z88_DIR}/z88ai.c"
  "${PLOP_Z88_DIR}/z88i1plop.c"
)

set(PLOP_Z88I2_SOURCES
  "${PLOP_Z88_DIR}/cshe88.c"
  "${PLOP_Z88_DIR}/ale88i.c"
  "${PLOP_Z88_DIR}/apla88.c"
  "${PLOP_Z88_DIR}/bapla88.c"
  "${PLOP_Z88_DIR}/bcshe88.c"
  "${PLOP_Z88_DIR}/bhexa88.c"
  "${PLOP_Z88_DIR}/bhpla88.c"
  "${PLOP_Z88_DIR}/blqua88.c"
  "${PLOP_Z88_DIR}/bqshe88.c"
  "${PLOP_Z88_DIR}/bspla88.c"
  "${PLOP_Z88_DIR}/bspur88.c"
  "${PLOP_Z88_DIR}/btetr88.c"
  "${PLOP_Z88_DIR}/dyn88i2.c"
  "${PLOP_Z88_DIR}/hexa88.c"
  "${PLOP_Z88_DIR}/hpla88.c"
  "${PLOP_Z88_DIR}/isod88.c"
  "${PLOP_Z88_DIR}/jaco88.c"
  "${PLOP_Z88_DIR}/lan88i2.c"
  "${PLOP_Z88_DIR}/lqua88.c"
  "${PLOP_Z88_DIR}/m1.c"
  "${PLOP_Z88_DIR}/m2.c"
  "${PLOP_Z88_DIR}/prfl88.c"
  "${PLOP_Z88_DIR}/qshe88.c"
  "${PLOP_Z88_DIR}/r1y88i.c"
  "${PLOP_Z88_DIR}/r4y88i.c"
  "${PLOP_Z88_DIR}/ri588i.c"
  "${PLOP_Z88_DIR}/spla88.c"
  "${PLOP_Z88_DIR}/spur88.c"
  "${PLOP_Z88_DIR}/tetr88.c"
  "${PLOP_Z88_DIR}/wlog88i2.c"
  "${PLOP_Z88_DIR}/z88bi.c"
  "${PLOP_Z88_DIR}/z88ci.c"
  "${PLOP_Z88_DIR}/z88i2plop.c"
)

foreach(_src IN LISTS PLOP_Z88I1_SOURCES PLOP_Z88I2_SOURCES)
  set_source_files_properties("${_src}" PROPERTIES LANGUAGE CXX)
endforeach()

add_executable(z88i1plop ${PLOP_Z88I1_SOURCES})
target_include_directories(z88i1plop PRIVATE "${PLOP_Z88_DIR}")
target_compile_definitions(z88i1plop PRIVATE FR_XDOUB FR_WIN95 gui_plop_version)
set_target_properties(z88i1plop PROPERTIES OUTPUT_NAME z88i1plop)

add_executable(z88i2plop ${PLOP_Z88I2_SOURCES})
target_include_directories(z88i2plop PRIVATE "${PLOP_Z88_DIR}")
target_compile_definitions(z88i2plop PRIVATE FR_XDOUB FR_WIN95 gui_plop_version)
set_target_properties(z88i2plop PROPERTIES OUTPUT_NAME z88i2plop)

install(TARGETS plop_cli z88i1plop z88i2plop RUNTIME DESTINATION .)

set(PLOP_OPTIONAL_RUNTIME_FILES
  "${CMAKE_CURRENT_SOURCE_DIR}/GuiPlop Users Manual.pdf"
  "${CMAKE_CURRENT_SOURCE_DIR}/plop_src/plop_xe10/gui_plop/z88.dyn"
  "${CMAKE_CURRENT_SOURCE_DIR}/plop_src/plop_xe10/gui_plop/z88i4.txt"
)

add_custom_target(plop_runtime_assets ALL
  COMMAND "${CMAKE_COMMAND}" -E make_directory "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
  COMMENT "Staging PLOP runtime assets"
)

foreach(_runtime_file IN LISTS PLOP_OPTIONAL_RUNTIME_FILES)
  if(EXISTS "${_runtime_file}")
    add_custom_command(TARGET plop_runtime_assets POST_BUILD
      COMMAND "${CMAKE_COMMAND}" -E copy_if_different "${_runtime_file}" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
    )
    install(FILES "${_runtime_file}" DESTINATION .)
  endif()
endforeach()

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/plop_src/plop_xe10/gui_plop/autocell")
  add_custom_command(TARGET plop_runtime_assets POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E copy_directory
      "${CMAKE_CURRENT_SOURCE_DIR}/plop_src/plop_xe10/gui_plop/autocell"
      "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/autocell"
  )
  install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/plop_src/plop_xe10/gui_plop/autocell" DESTINATION .)
endif()

if(PLOP_BUILD_QT_GUI)
  find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Gui Widgets QUIET)
  if(QT_FOUND)
    find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Widgets)

    add_executable(plop_gui_qt
      "${PLOP_GUI_DIR}/main.cpp"
      "${PLOP_GUI_DIR}/MainWindow.cpp"
      "${PLOP_GUI_DIR}/MainWindow.h"
      "${PLOP_GUI_DIR}/PlotWindow.cpp"
      "${PLOP_GUI_DIR}/PlotWindow.h"
      "${PLOP_GUI_DIR}/PartDimensionWindow.cpp"
      "${PLOP_GUI_DIR}/PartDimensionWindow.h"
      "${PLOP_GUI_DIR}/PlopCoreFacade.cpp"
      "${PLOP_GUI_DIR}/PlopCoreFacade.h"
      "${PLOP_GUI_DIR}/PlopQtRuntime.cpp"
      "${PLOP_GUI_DIR}/PlopQtRuntime.h"
    )
    set_target_properties(plop_gui_qt PROPERTIES
      AUTOMOC ON
      AUTOUIC OFF
      AUTORCC ON
      OUTPUT_NAME plop_gui_qt
    )
    target_include_directories(plop_gui_qt PRIVATE "${PLOP_CORE_DIR}" "${PLOP_GUI_DIR}")
    target_link_libraries(plop_gui_qt PRIVATE plop_core Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Gui Qt${QT_VERSION_MAJOR}::Widgets)
    add_dependencies(plop_gui_qt z88i1plop z88i2plop)

    install(TARGETS plop_gui_qt RUNTIME DESTINATION .)

    find_program(WINDEPLOYQT_EXECUTABLE windeployqt)
    if(WIN32 AND WINDEPLOYQT_EXECUTABLE)
      add_custom_target(plop_gui_qt_deploy
        COMMAND "${WINDEPLOYQT_EXECUTABLE}" "$<TARGET_FILE:plop_gui_qt>"
        DEPENDS plop_gui_qt
        COMMENT "Deploying Qt runtime next to plop_gui_qt"
      )
    endif()
  else()
    message(WARNING "Qt Widgets was not found. The plop_gui_qt target will not be generated until Qt is installed.")
  endif()
endif()
