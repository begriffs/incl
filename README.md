## Include/expand files

A simple preprocessor that can recursively include the contents of multiple
files into an output stream. (Think of it like "m4 lite.")

### Usage

```bash
echo -n "foo" > name.txt

cat << EOF | ./incl
Hello #incl(name.txt), how are you?

This is a template, #incl(name.txt).
EOF
```

### Installation

Because of make's default suffix rules, build simply with:

```
make incl
```

Optionally copy the binary to your path.
