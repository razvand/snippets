Build image:

```console
$ docker build -t my-print .
```

Run image with default (built-in) arguments:

```console
$ docker run --rm --name my-run -it my-print:latest 
Hello, World!
```

Run image with custom arguments:

```console
$ docker run --rm --name my-run -it my-print:latest ana are mere
ana are mere
```
