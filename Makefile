.PHONY: clean All

All:
	@echo "----------Building project:[ MerryChristmasOldver - Release ]----------"
	@cd "MerryChristmasOldver" && "$(MAKE)" -f  "MerryChristmasOldver.mk"
clean:
	@echo "----------Cleaning project:[ MerryChristmasOldver - Release ]----------"
	@cd "MerryChristmasOldver" && "$(MAKE)" -f  "MerryChristmasOldver.mk" clean
