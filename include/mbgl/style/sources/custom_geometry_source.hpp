#pragma once

#include <mbgl/actor/scheduler.hpp>
#include <mbgl/style/source.hpp>
#include <mbgl/util/geo.hpp>
#include <mbgl/util/geojson.hpp>
#include <mbgl/util/range.hpp>
#include <mbgl/util/constants.hpp>

namespace mbgl {

class OverscaledTileID;
class CanonicalTileID;
template <class T>
class Actor;

namespace style {

using TileFunction = std::function<void(const CanonicalTileID&)>;

class CustomTileLoader;

// NOTE: Any derived class must invalidate `weakFactory` in the destructor
class CustomGeometrySource final : public Source {
public:
    struct TileOptions {
        double tolerance = 0.375;
        uint16_t tileSize = util::tileSize_I;
        uint16_t buffer = 128;
        bool clip = false;
        bool wrap = false;
    };

    struct Options {
        TileFunction fetchTileFunction;
        TileFunction cancelTileFunction;
        Range<uint8_t> zoomRange = {0, 18};
        TileOptions tileOptions;
    };

public:
    CustomGeometrySource(std::string id, const CustomGeometrySource::Options& options);
    CustomGeometrySource(std::string id,
                         const CustomGeometrySource::Options& options,
                         const ThreadPoolHandle& threadPoolHandle);
    ~CustomGeometrySource() final;
    void loadDescription(FileSource&) final;
    void setTileData(const CanonicalTileID&, const GeoJSON&);
    void invalidateTile(const CanonicalTileID&);
    void invalidateRegion(const LatLngBounds&);
    // Private implementation
    class Impl;
    const Impl& impl() const;
    bool supportsLayerType(const mbgl::style::LayerTypeInfo*) const override;
    mapbox::base::WeakPtr<Source> makeWeakPtr() override { return weakFactory.makeWeakPtr(); }

protected:
    Mutable<Source::Impl> createMutable() const noexcept final;

private:
    ThreadPoolHandle threadPoolHandle;
    std::unique_ptr<Actor<CustomTileLoader>> loader;
    mapbox::base::WeakPtrFactory<Source> weakFactory{this};
    // Do not add members here, see `WeakPtrFactory`
};

template <>
inline bool Source::is<CustomGeometrySource>() const {
    return getType() == SourceType::CustomVector;
}

} // namespace style
} // namespace mbgl
