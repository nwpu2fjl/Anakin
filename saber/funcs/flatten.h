/* Copyright (c) 2018 Baidu, Inc. All Rights Reserved.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0
   
   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License. 
*/

#ifndef ANAKIN_SABER_FUNCS_FLATTEN_H
#define ANAKIN_SABER_FUNCS_FLATTEN_H

#include "saber/funcs/base.h"
#include "saber/funcs/impl/impl_define.h"
#include "saber/funcs/impl/impl_base.h"
namespace anakin{

namespace saber{

template<typename TargetType,
        DataType OpDtype,
        DataType inDtype = AK_FLOAT,
        DataType outDtype = AK_FLOAT,
        typename LayOutType_op = NCHW,
        typename LayOutType_in = NCHW,
        typename LayOutType_out = NCHW
>
class Flatten : public BaseFunc<
        Tensor<TargetType, inDtype, LayOutType_in>,
        Tensor<TargetType, outDtype, LayOutType_out>,
        Tensor<TargetType, OpDtype, LayOutType_op>,
        ImplBase,
        FlattenParam
> {
public:
    using BaseFunc<
            Tensor<TargetType, inDtype, LayOutType_in>,
            Tensor<TargetType, outDtype, LayOutType_out>,
            Tensor<TargetType, OpDtype, LayOutType_op>,
            ImplBase,
            FlattenParam>::BaseFunc;

    Flatten() = default;

    typedef Tensor<TargetType, inDtype, LayOutType_in> InDataTensor;
    typedef Tensor<TargetType, outDtype, LayOutType_out> OutDataTensor;
    typedef Tensor<TargetType, OpDtype, LayOutType_op> OpTensor;
    typedef FlattenParam<OpTensor> Param_t;
    typedef std::vector<InDataTensor *> Input_v;
    typedef std::vector<OutDataTensor *> Output_v;
    typedef std::vector<Shape> Shape_v;

    virtual SaberStatus compute_output_shape(const Input_v& input, Output_v& output, \
        Param_t& param) override {
        Shape shape_out = input[0]->valid_shape();
        CHECK_EQ(shape_out.dims(), 4) << "only support 4d(NCHW) layout";
        shape_out[1] = input[0]->valid_size() / input[0]->num();
        shape_out[2] = 1;
        shape_out[3] = 1;
        return output[0]->set_shape(shape_out);
    }
    //flatten ops do nothing
    virtual SaberStatus init_impl(ImplEnum implenum) override {
        return SaberSuccess;
    }

    //flatten ops do nothing
    virtual SaberStatus init(const Input_v& input, Output_v& output, Param_t& param,
            SaberImplStrategy strategy, ImplEnum implenum, Context<TargetType > &ctx) {
        return SaberSuccess;
    }
    //flatten ops do nothing
    virtual SaberStatus operator()(const Input_v& input, Output_v& output, Param_t& param, \
        Context<TargetType> &ctx) {

    }

private:

    virtual void pick_best_static() override {
        //! flatten only has saber implementation
        this->_best_impl = this->_impl[0];
    }

    virtual void pick_best_runtime(Input_v input, Output_v output, \
        Param_t& param, Context<TargetType> &ctx) override {
        //! flatten only has saber implementation
        this->_best_impl = this->_impl[0];
    }

    virtual void pick_best_specify(ImplEnum implenum) override {
        //! flatten only has saber implementation
        this->_best_impl = this->_impl[0];
    }

};

} //namespace saber

} //namespace anakin

#endif //ANAKIN_SABER_FUNCS_FLATTEN_H