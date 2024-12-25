# Helloworld with Containers

Build and run simple programs that print "Hello, World!" using containers.

Use `make` for different builds:

* Build images:

  ```console
  make images
  ```

* Create containers:

  ```console
  make containers
  ```

* Run with anonymous ephemeral containers:

  ```console
  make run-anon-static
  make run-anon-gcc-12
  make run-anon-gcc-13
  ```

* Run with named containers:

  ```console
  make clean
  make run-static
  make run-gcc-12
  make run-gcc-13
  ```
