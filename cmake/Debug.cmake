set(DEBUG_FLAGS -g)

if(DEBUG)
  message("Debug symbols loading...")
  add_compile_options(${DEBUG_FLAGS})
endif()
