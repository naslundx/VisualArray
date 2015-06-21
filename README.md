# VisualArray
A multi-language library for visualizing operations on array requiring minimal source code change, available under the Apache license (use, modify, share as you want for private and commercial use). Intended for teaching new students algorithms on arrays, for example the sorting algorithms. 

Feel free to participate with the development in any way possible, a goal is to have the library available in as many languages as possible. The full source code is available at: https://github.com/naslundx/VisualArray

## Guidelines
Every implementation should respect the following points. Some of these are just good practice, some are specific to this project.

- **Minimal source code change**: The user should be required minimal changes (preferably just one) to run the visualization on existing implementation.
- **Mimic the array**: Overload operators such as [], =, == etc. between instances of VisualArray and between VisualArray and the default language array. Note that this varies between languages, the append() function exists for arrays (lists) in Python, but not in C++.
- **Don't be gentle**: If the array would normally crash (for example using an incorrect index), so should the this class. This does not apply to graphics functions because they are specific to VisualArray and should do error-checking.
- **Standard graphics library**: Use a graphics library for the rendering that is standard, easy to download and install, and cross-platform (Windows, Mac OS, Linux). Separate the rendering code from the engine code.
- **Interactivity**: Allow for play, pause, step back, step forward, go to beginning, go to end using both GUI and keyboard shortcuts.
- **Similarity**: Respect good practice for respective language, but also follow the overall structure from other implementations.
- **Examples**: Include examples using different algorithms.
- **Graphics**: Support coloring and highlighting of specific elements and separating the array into subarrays.
- **Minimalistic**: Despite the above, do not implement functions that are not usually part of the array syntax for the language. This means == between arrays is OK in Python, but not in Java.

## Status
Please feel free to help out.

- **Python**: Working. Restart and step back currently not implemented. GUI problems. No animations. Graphics in Tkinter.
- **C++**: Partially works. Graphics problems. GUI not implemented. Graphics in SFML.
- **C#**: Not working. Engine not finished and GUI not implemented. Graphics in SFML.
- (**Javascript** Not started.)
- (**Java**: Not started.)

The above five languages are of current focus, although it's unclear how well this can be done in Java. Perl and Ruby may be future additions.
