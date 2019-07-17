# xna-lite

based on Microsoft.Xna.Framework. This started as doran_xna.framework. But vala has some issues.
it did however, show that a c/c++ version is feasible. 

xna is 2 things: a framework, and a content pipeline. The content pipeline precompiles and packages assets into *.xnb files. This will not support xnb, and uses raw data instead, such as *.png, *.json, *.glsl files. It will be a framework with a shape similar to, and inspited by, the xna.framework.

c/cc+ drives me nuts with all the boilrplate and back & forth synchonization whith *.h and *.cpp. By creating my library in a header library, I can do away with all the two file crap, and just focus on code.