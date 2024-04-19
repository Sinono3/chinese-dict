project('chinese-dict', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3', 'cpp_std=c++14'])

fltk_dep = dependency('fltk')

executable('chinese-dict',
           'src/main.cpp',
           install: true, dependencies: [fltk_dep])
