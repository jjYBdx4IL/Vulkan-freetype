# Vulkan Rendering 🌋 

A minimally configurable wrapper around the creation of Vulkan rendering pipelines.

## API

> Proposed: Work in Progress

Much of Vulkan’s infamous [800+ lines of code to render a triangle](https://www.reddit.com/r/vulkan/comments/512jvs/does_it_really_take_800_to_1000_lines_of_code/) is hardware selection and configuration. The C++ API herein minimizes that boilerplate by allowing the programmer to just specify requirements. 

The complete Vulkan API is available for rendering; it is not wrapped or simplified.

##### Simple Example

```cpp
auto renderer = forge::renderer([ ] (auto& with) {
   // ...
});

// the rendering loop is then just:
renderer([&] (VkDevice device, VkCommandBuffer command_buffer) {
	
});
```







## Additional Features

### Text

> Text renderering is based upon a demo by [Dávid Kocsis](https://github.com/kocsis1david/font-demo)

Text is rendered [directly](https://github.com/bwoods/Vulkan/wiki/Text-Rendering) from font outlines.

- [x] “Lorem Ipsum” rendering
- [ ] Dynamic text rendering
- [ ] Fallback font handling

### Bezier

As the text renderer is extracting Bezier curves from the fonts, directly rendering Bezier curves should be relatively easy to add.

- [ ] bezier API
- [ ] rectangle API
- [ ] line API
- [ ] [squircle](https://www.paintcodeapp.com/news/code-for-ios-7-rounded-rectangles) API

