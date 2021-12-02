## Changes

Fixed stuff to make it work with MSVC 2019, Freetype 2.11.0, and Vulkan SDK 1.2.198.0.

## Description

Text is rendered [directly](https://github.com/bwoods/Vulkan/wiki/Text-Rendering) from font outlines.

You need to clone (checkout) the repository using the `--recurse-submodules` option.

## Performance

AMD Ryzen 5600X + GTX 1060: one CPU core at limit (90% of time spent in append_text() building the instance buffer from the raw text input string), GPU usage around 15% (debug mode). 600+ fps in debug mode, 4000+ fps in release mode.

## Conclusion

Works, but is it worth the additional CPU and GPU load?

## Sources

* https://github.com/bwoods/Vulkan
* Text renderering is based upon a demo by [Dávid Kocsis](https://github.com/kocsis1david/font-demo)

