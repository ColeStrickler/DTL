# Run the host simulator tests from the DTL repository root.
.PHONY: test-run
test-run:
	$(MAKE) -C src test-run
