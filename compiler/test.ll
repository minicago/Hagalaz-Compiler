()
malloc 16 -> $4
add $4, 0 -> $5
store 10 -> $5
add $4, 4 -> $6
store 2 -> $6
add $4, 8 -> $7
store 2 -> $7
add $4, 12 -> $8
store 4 -> $8
f
($9,)
load $9 -> $11
add 4, $11 -> $13
load $9 -> $14
add 4, $14 -> $16
load $16 -> $17
add $17, 1 -> $18
store $18 -> $13
load $9 -> $19
add 0, $19 -> $21
load $21 -> $22
return $22
malloc 4 -> $9

ff
($23,)
load $23 -> $25
add 8, $25 -> $27
call f($27, ) -> $28
malloc 4 -> $23

main
()
malloc 4 -> $30
call getint() -> $31
store $31 -> $30
malloc 4 -> $32
call getint() -> $33
store $33 -> $32
load $30 -> $34
load $32 -> $35
add $34, $35 -> $36
return $36


