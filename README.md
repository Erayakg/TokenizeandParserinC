# TokenizeandParserinC
El-Ceziri işlemcinin Assembler dilinin komutları ve grameri referans alınarak tokenleştirme parser işlemi yapılmıştır.

#Gramer kuralları

<program> -> <aritmetik> | <mantıksal> | <dallanma>
<aritmetik> ->TOP <op>,<op> | CRP <op>,<op> | BOL <op>,<op> | CIK <op>,<op> | ATM 
<op>,<op>
<mantıksal>  -> VE <op>,<op> | VEY <op>,<op>
<dallanma> -> DS <etiket> | DSD <etiket> | DAL <etiket> | DK <etiket> | DB <etiket>
<op> ->AX | BX | CX | DX | [<sabit>] | <sabit>
<sabit> -> 0 | 1 | 2 | …. | 255
<etiket>  -> ETIKET1 | ETIKET2 | … | ETIKET9
