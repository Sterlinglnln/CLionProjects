#include <iostream>
#include <librealsense2/rs.hpp>

int main() {
    try {
        rs2::context ctx;
        auto device = ctx.query_devices();
        if (device.size() == 0) {
            std::cout << "No devices found." << std::endl;
            return -1;
        }

        std::cout << "Found devices: " << device.size() << std::endl;

        rs2::pipeline pipe;

        rs2::config cfg;
        cfg.enable_stream(RS2_STREAM_COLOR, 640, 480, RS2_FORMAT_RGB8, 30);
        cfg.enable_stream(RS2_STREAM_DEPTH, 640, 480, RS2_FORMAT_Z16, 30);

        std::cout << "Starting realsense pipeline..." << std::endl;

        auto profile = pipe.start(cfg);
        auto frames = pipe.wait_for_frames();

        rs2::video_frame color = frames.get_color_frame();
        rs2::video_frame depth = frames.get_depth_frame();

        std::cout << "color frame: "
                  << color.get_width() << "x" << color.get_height() << std::endl;
        std::cout << "depth frame: "
                  << depth.get_width() << "x" << depth.get_height() << std::endl;

        pipe.stop();
        std::cout << "Stopping realsense pipeline..." << std::endl;
    }
    catch (rs2::error& e) {
        std::cerr << "RealSense error: " << e.what() << std::endl;
    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    return 0;
}
