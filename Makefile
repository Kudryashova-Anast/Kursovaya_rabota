.PHONY: clean All

All:
	@echo "----------Building project:[ LicenseChecker - Debug ]----------"
	@cd "LicenseChecker" && "$(MAKE)" -f  "LicenseChecker.mk"
clean:
	@echo "----------Cleaning project:[ LicenseChecker - Debug ]----------"
	@cd "LicenseChecker" && "$(MAKE)" -f  "LicenseChecker.mk" clean
