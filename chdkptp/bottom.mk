DFILES=$(SRCS:%.c=$(DEP_DIR)/%.d)

-include $(DFILES)
