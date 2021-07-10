# Test K8s TCP Probe

## Setup

Fist download the following set of tools:

```sh
mkdir tools
curl -Lo ./tools/kind https://kind.sigs.k8s.io/dl/v0.11.1/kind-linux-amd64
chmod +x ./tools/kind

curl -Lo ./tools/kubectl "https://dl.k8s.io/release/$(curl -L -s https://dl.k8s.io/release/stable.txt)/bin/linux/amd64/kubectl"
chmod +x ./tools/kubectl

curl -Lo ./tools/bazelisk https://github.com/bazelbuild/bazelisk/releases/download/v1.9.0/bazelisk-linux-amd64
chmod +x ./tools/bazelisk

export PATH="$(pwd)/tools/:${PATH}"
```

Then build the docker image and create a cluster

```sh
kind create cluster  --name kind
bazelisk build //:app.tar
kind load image-archive bazel-bin/app.tar --name kind

kubectl apply -f deployment.yml

kubectl logs -f $(kubectl get pods | egrep -o 'sample-deployment-[^ ]*')
```

## Cleanup

```sh
kind delete cluster --name kind
rm -rf ~/.cache/bazel/ ~/.cache/bazelisk/
```
