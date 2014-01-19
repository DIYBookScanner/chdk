depend: depend-recursive $(OBJS:.o=.d)

#ifneq ($(strip $(OBJS)),)
#-include $(OBJS:%.o=.dep/%.d)
#endif


# Define empty recipes for source files (including the makefiles)
# to prevent make from trying implicit rules to create them. Speeds up build process
$(topdir)bottom.inc: ;
