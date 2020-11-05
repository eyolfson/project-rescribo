add_library(project-rescribo SHARED
  annotation.cpp
  annotations.cpp
  attribute.cpp
  attributes.cpp
  class_file.cpp
  code.cpp
  constant_pool.cpp
  constant_pool_entry.cpp
  field.cpp
  fields.cpp
  instruction.cpp
  interfaces.cpp
  method.cpp
  methods.cpp
  stack_map_table.cpp
)
set_property(
  TARGET project-rescribo PROPERTY CXX_STANDARD 17
)
install(TARGETS project-rescribo)
