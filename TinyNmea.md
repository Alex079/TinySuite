## [TinyNmea](src/TinyNmea.h)

### Struct NmeaParser

|Field|Description|
|-|-|
|type|Last three symbols of NMEA sentence type designator. Used in parser lookup, type match is "ends with", case-sensitive.|
|call|A pointer to parser function to invoke when the matching NMEA sentence is received. The function may accept "term" (the C-String containing NMEA term) and "termIndex" (a 0-based index of the term in the sentence).|

### Class TinyNmea

|Method|Parameters|Return|Description|
|-|-|-|-|
|(init)|parsers, parsersCount||Instantiate the parser. The "parsers" is the array of "parsersCount" size, which contains "NmeaParser" structures.|
|next|char||Feed the parser with one character.|
