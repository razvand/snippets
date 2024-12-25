OPTIONS = gcc-13 gcc-12 static
DOCKERFILES = $(OPTIONS:%=Dockerfile.%)
IMAGES = $(OPTIONS:%=helloworld-%)
CONTAINERS = $(IMAGES:%=cnt-%)

.PHONY: all clean

all: images

images: $(IMAGES)

helloworld-%: Dockerfile.%
	docker build -t $@ -f $< .

containers: $(CONTAINERS)

cnt-helloworld-%: helloworld-%
	docker create --name $@ -i -t $^

run-anon-%: helloworld-%
	docker run --rm -t $^

run-%: cnt-helloworld-%
	docker start --attach -i $^

clean:
	-docker stop $(CONTAINERS)
	-docker rm $(CONTAINERS)
