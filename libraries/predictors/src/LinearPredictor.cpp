////////////////////////////////////////////////////////////////////////////////////////////////////
//
//  Project:  Embedded Machine Learning Library (EMLL)
//  File:     LinearPredictor.cpp (predictors)
//  Authors:  Ofer Dekel
//
////////////////////////////////////////////////////////////////////////////////////////////////////

#include "LinearPredictor.h"

// stl
#include <memory>

namespace predictors
{
    LinearPredictor::LinearPredictor() : _b(0)
    {}

    LinearPredictor::LinearPredictor(uint64_t dim) : _w(dim), _b(0)
    {}

    void LinearPredictor::Reset()
    {
        _w.Reset();
        _b = 0;
    }

    double LinearPredictor::Predict(const dataset::IDataVector& dataVector) const
    {
        return dataVector.Dot(_w) + _b;
    }

    std::vector<double> LinearPredictor::GetWeightedElements(const dataset::IDataVector& dataVector) const
    {
        std::vector<double> weightedElements(_w.Size());
        dataVector.AddTo(weightedElements);
        for (size_t i = 0; i < _w.Size(); ++i)
        {
            weightedElements[i] *= _w[i];
        }
        return weightedElements;
    }

    void LinearPredictor::Scale(double scalar)
    {
        _w.Scale(scalar);
        _b *= scalar;
    }

    void LinearPredictor::Serialize(utilities::Serializer& serializer) const
    {
        std::vector<double> weights = _w;
        serializer.Serialize("w", weights);
        serializer.Serialize("b", _b);
    }

    void LinearPredictor::Deserialize(utilities::Deserializer& serializer, utilities::SerializationContext& context)
    {
        std::vector<double> weights;
        serializer.Deserialize("w", weights, context);
        _w = weights;
        serializer.Deserialize("b", _b, context);
    }
}
