#include <mbgl/style/image.hpp>
#include <mbgl/style/image_impl.hpp>
#include <mbgl/util/exception.hpp>

namespace mbgl {
namespace style {

Image::Image(std::string id,
             PremultipliedImage&& image,
             const float pixelRatio,
             bool sdf,
             ImageStretches stretchX,
             ImageStretches stretchY,
             const std::optional<ImageContent>& content,
             const std::optional<TextFit>& textFitWidth,
             const std::optional<TextFit>& textFitHeight)
    : baseImpl(makeMutable<Impl>(std::move(id),
                                 std::move(image),
                                 pixelRatio,
                                 sdf,
                                 std::move(stretchX),
                                 std::move(stretchY),
                                 content,
                                 textFitWidth,
                                 textFitHeight)) {}

std::string Image::getID() const {
    return baseImpl->id;
}

Image::Image(const Image&) = default;

const PremultipliedImage& Image::getImage() const {
    return baseImpl->image;
}

bool Image::isSdf() const {
    return baseImpl->sdf;
}

float Image::getPixelRatio() const {
    return baseImpl->pixelRatio;
}

const ImageStretches& Image::getStretchX() const {
    return baseImpl->stretchX;
}

const ImageStretches& Image::getStretchY() const {
    return baseImpl->stretchY;
}

const std::optional<ImageContent>& Image::getContent() const {
    return baseImpl->content;
}

const std::optional<TextFit>& Image::getTextFitWidth() const {
    return baseImpl->textFitWidth;
}

const std::optional<TextFit>& Image::getTextFitHeight() const {
    return baseImpl->textFitHeight;
}
} // namespace style
} // namespace mbgl
