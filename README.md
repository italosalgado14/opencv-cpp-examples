# OpenCV C++ Examples

C++ implementations of OpenCV algorithms, based on:

> *OpenCV 4 Computer Vision Application Programming Cookbook* — Fourth Edition
> David Millán Escrivá, Robert Laganière

Each subdirectory is a self-contained CMake project covering a specific topic from the book.

---

## Examples

| Directory | Topic |
|-----------|-------|
| `04_ROI` | Region of Interest — overlaying a logo onto an image using `cv::Rect` |
| `05_AccessingPixel` | Pixel-level access — adding salt noise via direct pointer iteration |
| `06_ReduceColor` | Color reduction — quantizing pixel values to reduce the color palette |
| `30_ComparingColors` | Color detection — finding pixels that match a target color (`ColorDetector` class) |
| `32_representingHSB` | HSB/HSV color space — representing and manipulating hue, saturation, brightness |
| `40_histogram` | Histograms — computing and displaying grayscale and color histograms |
| `41_histogramColor` | Color histograms — back-projection and content-based image matching (`ContentFinder`) |
| `43_meanshift` | Mean shift — tracking objects using histogram back-projection |
| `44_countingPixels` | Counting pixels — integral images for fast area sums |
| `44_countingPixels2` | Counting pixels (variant) — combining histograms and integral images |
| `53_segmentingWS` | Watershed segmentation — marker-based image segmentation |
| `70_canny` | Edge detection — Canny edge detector and Hough line transform |
| `71_ExtracCompon` | Connected components — extracting and labeling connected regions |
| `120_RPWvideos` | Video processing — frame-by-frame processing with a reusable `VideoProcessor` class |
| `121_BGFG` | Background/foreground segmentation — moving object detection in video using `BGFGSegmentor` |

---

## Build

Each example uses CMake. To build one:

```bash
cd <example_directory>
cmake -B build
cmake --build build
```

Requires OpenCV 4 installed on the system.

---

## Notes

Originally hosted at `https://gitlab.com/italo.salgado.14/opencv-c-examples`
