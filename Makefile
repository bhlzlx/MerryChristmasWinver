.PHONY: clean All

All:
	@echo "----------Building project:[ MerryChristmas - Debug ]----------"
	@cd "MerryChristmas" && "$(MAKE)" -f  "MerryChristmas.mk"
clean:
	@echo "----------Cleaning project:[ MerryChristmas - Debug ]----------"
	@cd "MerryChristmas" && "$(MAKE)" -f  "MerryChristmas.mk" clean
