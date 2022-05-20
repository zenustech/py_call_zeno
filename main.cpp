#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <zeno/zeno.h>
#include <zeno/types/PrimitiveObject.h>
#include <zeno/types/NumericObject.h>
#include <zeno/utils/logger.h>
#include <iostream>
#include <sstream>
#include <fstream>

std::unique_ptr<zeno::Scene> scene;

std::string read_string_from_file(std::string file_path) {
    const std::ifstream input_stream(file_path, std::ios_base::binary);

    if (input_stream.fail()) {
        throw std::runtime_error("Failed to open file");
    }

    std::stringstream buffer;
    buffer << input_stream.rdbuf();

    return buffer.str();
}


void createScene() {
    scene = zeno::createScene();
}

void load_scene(std::string path) {
    std::string content = read_string_from_file(path);
    scene->loadScene(content.c_str());
    scene->switchGraph("main");
}

void applyGraph() {
    scene->switchGraph("main");
    scene->getGraph().applyGraph();
}

void setNodeInputFloat(std::string nid, std::string par, float value) {
    scene->getGraph().setNodeInput(nid, par, value);
}
void setNodeInputVec2(std::string nid, std::string par, float x, float y) {
    scene->getGraph().setNodeInput(nid, par, zeno::vec2f(x, y));
}
void setNodeInputVec3(std::string nid, std::string par, float x, float y, float z) {
    scene->getGraph().setNodeInput(nid, par, zeno::vec3f(x, y, z));
}
void setNodeInputVec4(std::string nid, std::string par, float x, float y, float z, float w) {
    scene->getGraph().setNodeInput(nid, par, zeno::vec4f(x, y, z, w));
}
void setNodeInputInt(std::string nid, std::string par, int value) {   
    scene->getGraph().setNodeInput(nid, par, value);
}

void setNodeInputString(std::string nid, std::string par, std::string value) {   
    scene->getGraph().setNodeInputString(nid, par, value);
}

void setNodeParamFloat(std::string nid, std::string par, float value) {
    scene->getGraph().setNodeParam(nid, par, value);
}

void setNodeParamInt(std::string nid, std::string par, int value) {   
    scene->getGraph().setNodeParam(nid, par, value);
}

void setNodeParamString(std::string nid, std::string par, std::string value) {   
    scene->getGraph().setNodeParam(nid, par, value);
}

float getGraphOutputFloat(std::string nid) {
    auto v = std::get<float>(zeno::safe_any_cast<zeno::NumericValue>(scene->getGraph().getGraphOutput2(nid)));
    return v;
}

std::tuple<float, float> getGraphOutputVec2(std::string nid) {
    auto v = std::get<zeno::vec2f>(zeno::safe_any_cast<zeno::NumericValue>(scene->getGraph().getGraphOutput2(nid)));
    return {v[0], v[1]};
}

std::tuple<float, float, float> getGraphOutputVec3(std::string nid) {
    auto v = std::get<zeno::vec3f>(zeno::safe_any_cast<zeno::NumericValue>(scene->getGraph().getGraphOutput2(nid)));
    return {v[0], v[1], v[2]};
}

std::tuple<float, float, float, float> getGraphOutputVec4(std::string nid) {
    auto v = std::get<zeno::vec3f>(zeno::safe_any_cast<zeno::NumericValue>(scene->getGraph().getGraphOutput2(nid)));
    return {v[0], v[1], v[2], v[3]};
}

PYBIND11_MODULE(embedtest, m) {
    m.def("createScene", createScene);
    m.def("load_scene", load_scene);
    m.def("applyGraph", applyGraph);
    m.def("setNodeInputFloat", setNodeInputFloat);
    m.def("setNodeInputVec2", setNodeInputVec2);
    m.def("setNodeInputVec3", setNodeInputVec3);
    m.def("setNodeInputVec4", setNodeInputVec4);
    m.def("setNodeInputInt", setNodeInputInt);
    m.def("setNodeInputString", setNodeInputString);
    m.def("setNodeParamFloat", setNodeParamFloat);
    m.def("setNodeParamInt", setNodeParamInt);
    m.def("setNodeParamString", setNodeParamString);
    m.def("getGraphOutputFloat", getGraphOutputFloat);
    m.def("getGraphOutputVec2", getGraphOutputVec2);
    m.def("getGraphOutputVec3", getGraphOutputVec3);
    m.def("getGraphOutputVec4", getGraphOutputVec4);
}

// void end_up() {
//     auto prim = scene->getGraph().getGraphOutput<zeno::PrimitiveObject>("outPrim");
//     auto &pos = prim->attr<zeno::vec3f>("pos");
//     for (int i = 0; i < pos.size(); i++) {
//         printf("pos[%d]: (%f, %f, %f)\n", i, pos[i][0], pos[i][1], pos[i][2]);
//     }
// }

// int main() {
//     createScene();
//     load_scene("fuck1.json");
//     for (int frame = 0; frame < 10; frame++) {
//         setNodeInputFloat("f8a42c58-PackNumericVec", "x", (float)frame);
//         applyGraph();
//     }

//     zeno::vec3f v = std::get<zeno::vec3f>(zeno::safe_any_cast<zeno::NumericValue>(scene->getGraph().getGraphOutput2("output1")));
//     auto x = getGraphOutputVec3("output1");

//     return 0;
// }