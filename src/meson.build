project('twol', 'cpp', version : '0.1', default_options : ['warning_level=3','cpp_std=c++17'])


include_dirs = \
[ \
  include_directories('../ext_deps/ftxui/include'), \
  include_directories('../ext_deps/ftxui/include/component'), \
  include_directories('../ext_deps/ftxui/include/dom'), \
  include_directories('../ext_deps/inifile-cpp') \
]

# ftxui_src = \
# [ \
#   '../ext_deps/ftxui/src/dom/automerge.cpp', \
#   '../ext_deps/ftxui/src/dom/benchmark.cpp', \
#   '../ext_deps/ftxui/src/dom/blink.cpp', \
#   '../ext_deps/ftxui/src/dom/blink_test.cpp', \
#   '../ext_deps/ftxui/src/dom/bold.cpp', \
#   '../ext_deps/ftxui/src/dom/bold_test.cpp', \
#   '../ext_deps/ftxui/src/dom/border.cpp', \
#   '../ext_deps/ftxui/src/dom/border_test.cpp', \
#   '../ext_deps/ftxui/src/dom/box_helper.cpp', \
#   '../ext_deps/ftxui/src/dom/canvas.cpp', \
#   '../ext_deps/ftxui/src/dom/canvas_test.cpp', \
#   '../ext_deps/ftxui/src/dom/clear_under.cpp', \
#   '../ext_deps/ftxui/src/dom/color.cpp', \
#   '../ext_deps/ftxui/src/dom/color_test.cpp', \
#   '../ext_deps/ftxui/src/dom/composite_decorator.cpp', \
#   '../ext_deps/ftxui/src/dom/dbox.cpp', \
#   '../ext_deps/ftxui/src/dom/flexbox_helper.cpp', \
#   '../ext_deps/ftxui/src/dom/flexbox_helper_test.cpp', \
#   '../ext_deps/ftxui/src/dom/flex.cpp', \
#   '../ext_deps/ftxui/src/dom/focus.cpp', \
#   '../ext_deps/ftxui/src/dom/frame.cpp', \
#   '../ext_deps/ftxui/src/dom/gauge.cpp', \
#   '../ext_deps/ftxui/src/dom/gauge_test.cpp', \
#   '../ext_deps/ftxui/src/dom/graph.cpp', \
#   '../ext_deps/ftxui/src/dom/gridbox.cpp', \
#   '../ext_deps/ftxui/src/dom/gridbox_test.cpp', \
#   '../ext_deps/ftxui/src/dom/hbox.cpp', \
#   '../ext_deps/ftxui/src/dom/hbox_test.cpp', \
#   '../ext_deps/ftxui/src/dom/hyperlink.cpp', \
#   '../ext_deps/ftxui/src/dom/hyperlink_test.cpp', \
#   '../ext_deps/ftxui/src/dom/inverted.cpp', \
#   '../ext_deps/ftxui/src/dom/linear_gradient.cpp', \
#   '../ext_deps/ftxui/src/dom/scroll_indicator.cpp', \
#   '../ext_deps/ftxui/src/dom/scroll_indicator_test.cpp', \
#   '../ext_deps/ftxui/src/dom/selection.cpp', \
#   '../ext_deps/ftxui/src/dom/selection_style.cpp', \
#   '../ext_deps/ftxui/src/dom/selection_test.cpp', \
#   '../ext_deps/ftxui/src/dom/separator.cpp', \
#   '../ext_deps/ftxui/src/dom/separator_test.cpp', \
#   '../ext_deps/ftxui/src/dom/size.cpp', \
#   '../ext_deps/ftxui/src/dom/spinner.cpp', \
#   '../ext_deps/ftxui/src/dom/spinner_test.cpp', \
#   '../ext_deps/ftxui/src/dom/striketrough.cpp', \
#   '../ext_deps/ftxui/src/dom/table.cpp', \
#   '../ext_deps/ftxui/src/dom/table_test.cpp', \
#   '../ext_deps/ftxui/src/dom/text.cpp', \
#   '../ext_deps/ftxui/src/dom/text_test.cpp', \
#   '../ext_deps/ftxui/src/dom/underlined.cpp', \
#   '../ext_deps/ftxui/src/dom/underlined_double.cpp', \
#   '../ext_deps/ftxui/src/dom/dbox_test.cpp', \
#   '../ext_deps/ftxui/src/dom/dim.cpp', \
#   '../ext_deps/ftxui/src/dom/dim_test.cpp', \
#   '../ext_deps/ftxui/src/dom/flexbox_config.cpp', \
#   '../ext_deps/ftxui/src/dom/flexbox.cpp', \
#   '../ext_deps/ftxui/src/dom/flexbox.cpp', \
#   '../ext_deps/ftxui/src/dom/linear_gradient_test.cpp', \
#   '../ext_deps/ftxui/src/dom/node.cpp', \
#   '../ext_deps/ftxui/src/dom/node_decorator.cpp', \
#   '../ext_deps/ftxui/src/dom/paraghaph.cpp', \
#   '../ext_deps/ftxui/src/dom/reflect.cpp', \
#   '../ext_deps/ftxui/src/dom/underlined_test.cpp', \
#   '../ext_deps/ftxui/src/dom/util.cpp', \
#   '../ext_deps/ftxui/src/dom/vbox.cpp', \
#   '../ext_deps/ftxui/src/dom/vbox_test.cpp', \
#   '../ext_deps/ftxui/src/component/animation.cpp', \
#   '../ext_deps/ftxui/src/component/animation_test.cpp', \
#   '../ext_deps/ftxui/src/component/button.cpp', \
#   '../ext_deps/ftxui/src/component/button_test.cpp', \
#   '../ext_deps/ftxui/src/component/catch_event.cpp', \
#   '../ext_deps/ftxui/src/component/checkbox.cpp', \
#   '../ext_deps/ftxui/src/component/collapsible.cpp', \
#   '../ext_deps/ftxui/src/component/collapsible_test.cpp', \
#   '../ext_deps/ftxui/src/component/component.cpp', \
#   '../ext_deps/ftxui/src/component/component_fuzzer.cpp', \
#   '../ext_deps/ftxui/src/component/component_options.cpp', \
#   '../ext_deps/ftxui/src/component/component_tests.cpp', \
#   '../ext_deps/ftxui/src/component/container.cpp', \
#   '../ext_deps/ftxui/src/component/container_test.cpp', \
#   '../ext_deps/ftxui/src/component/dropdown.cpp', \
#   '../ext_deps/ftxui/src/component/event.cpp', \
#   '../ext_deps/ftxui/src/component/hoverable.cpp', \
#   '../ext_deps/ftxui/src/component/hoverable_test.cpp', \
#   '../ext_deps/ftxui/src/component/input.cpp', \
#   '../ext_deps/ftxui/src/component/input_test.cpp', \
#   '../ext_deps/ftxui/src/component/loop.cpp', \
#   '../ext_deps/ftxui/src/component/maybe.cpp', \
#   '../ext_deps/ftxui/src/component/menu.cpp', \
#   '../ext_deps/ftxui/src/component/menu_test.cpp', \
#   '../ext_deps/ftxui/src/component/modal.cpp', \
#   '../ext_deps/ftxui/src/component/modal_test.cpp', \
#   '../ext_deps/ftxui/src/component/radiobox.cpp', \
#   '../ext_deps/ftxui/src/component/radiobox_test.cpp', \
#   '../ext_deps/ftxui/src/component/renderer.cpp', \
#   '../ext_deps/ftxui/src/component/resizable_split.cpp', \
#   '../ext_deps/ftxui/src/component/resizable_split_test.cpp', \
#   '../ext_deps/ftxui/src/component/screen_interactive.cpp', \
#   '../ext_deps/ftxui/src/component/screen_interactive_test.cpp', \
#   '../ext_deps/ftxui/src/component/slider.cpp', \
#   '../ext_deps/ftxui/src/component/slider_test.cpp', \
#   '../ext_deps/ftxui/src/component/terminal_input_parser.cpp', \
#   '../ext_deps/ftxui/src/component/terminal_input_parser_test.cpp', \
#   '../ext_deps/ftxui/src/component/terminal_input_parser_test_fuzzer.cpp', \
#   '../ext_deps/ftxui/src/component/toggle_test.cpp', \
#   '../ext_deps/ftxui/src/component/util.cpp', \
#   '../ext_deps/ftxui/src/component/window.cpp', \
#   '../ext_deps/ftxui/src/screen/box.cpp', \
#   '../ext_deps/ftxui/src/screen/color.cpp', \
#   '../ext_deps/ftxui/src/screen/color_info.cpp', \
#   '../ext_deps/ftxui/src/screen/color_test.cpp', \
#   '../ext_deps/ftxui/src/screen/image.cpp', \
#   '../ext_deps/ftxui/src/screen/string.cpp', \
#   '../ext_deps/ftxui/src/screen/screen.cpp', \
#   '../ext_deps/ftxui/src/screen/string_internal.cpp', \
#   '../ext_deps/ftxui/src/screen/string_test.cpp', \
#   '../ext_deps/ftxui/src/screen/string_test.cpp', \
#   '../ext_deps/ftxui/src/screen/terminal.cpp', \
#   '../ext_deps/ftxui/src/screen/util.cpp', \
#   '../ext_deps/ftxui/src/util/ref_test.cpp' \
# ]
# 
# Specify FTXUI library location
ftxui_dep = dependency('ftxui', required: false)

if not ftxui_dep.found()
  # Use FTXUI as a subproject if not installed
  subdir('ftxui')
  ftxui_dep = declare_dependency(
    include_directories: include_directories('../ext_deps/ftxui/include'),
    link_with: static_library('ftxui', '../ext_deps/ftxui/src/*.cpp'),
  )
endif
twol_sources = \
[ \
  'twol.cpp', \
  'config.cpp', \
  'twol_list.cpp', \
  'wake_on_lan.cpp', \
  'tui.cpp', \
]


exe = executable('twol', twol_sources, dependencies: [ftxui_dep], install : true)

test('basic', exe)
