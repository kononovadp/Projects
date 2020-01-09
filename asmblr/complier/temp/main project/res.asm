|data|segment||
|Data1|segment||
|name1|db|'Hello'|
|field1|dw|3131h|
|Data1|ends||
|data2|segment||
|qwer|db|1010b|
|asdf|db|1010b|
|zxcv|db|'hello'|
|rtyu|db|1010b|
|qwer1|dw|1010h|
|asdf1|dw|1010h|
|zxcv1|dw|2020h|
|rtyu1|dw|1010|
|qwer2|dd|1010|
Text constant can be used for db only!
|asdf2|dd|1010h|
Text constant can be used for db only!
|zxcv2|dd|2020|
Text constant can be used for db only!
|rtyu2|dd|1010b|
Text constant can be used for db only!
|qwer5|db|1010b|
|asdf5|db|1010b|
|zxcv7|dw|2020h|
|zxcv9|dw|2020|
|data2|ends||
|data|ends||
|code|segment||
|code1|segment||
|assume|ds|data1|cs|code1 |
|inc|cx||
|dec|di||
|adc|bh|bl|
|cmp|dx|80h|
|jb|||
|assume|ds|data2|cs|code1|
|xor|al|01h|
|adc|ax|si|
|cmp|dx|1010b|
|jb|||
|sal|di|1|
|or|dh|cl|
|cli|||
|code1|ends||
|code|ends||
|end|||

Segments:
data
Data1
data2
code
code1

Identifiers:
name1
field1
qwer
asdf
zxcv
rtyu
qwer1
asdf1
zxcv1
rtyu1
qwer2
asdf2
zxcv2
rtyu2
qwer5
asdf5
zxcv7
zxcv9
