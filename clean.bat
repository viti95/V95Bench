wmake -f make16.mk clean
wmake -f make16.mk v95_16.exe
md build
copy v95_16.exe .\build\v95_16.exe

wmake -f make32.mk clean
wmake -f make32.mk v95_32.exe
sb -r v95_32.exe
ss v95_32.exe dos32a.d32
md build
copy v95_32.exe .\build\v95_32.exe
