include config.mk

$(BUILD_DIR)/%.cc.o: %.cc
	$(BUILD_DIR_GUARD)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BUILD_DIR)/$(GOAL): $(OBJS)
	$(CXX)  $(CXXFLAGS) -o $@ $^

clear_obj:
	rm -r ${BUILD_DIR}
