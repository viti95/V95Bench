wmake -f make32.mk clean
wmake -f make32.mk v95_32.exe
sb -r v95_32.exe
ss v95_32.exe dos32a.d32
md build
copy v95_32.exe .\build\v95_32.exe
