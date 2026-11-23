# Run the host simulator tests from the DTL repository root.
.PHONY: test-run example-run
test-run:
	$(MAKE) -C src test-run

example-run:
	$(MAKE) -C src example-run
