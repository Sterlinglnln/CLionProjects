#include <iostream>
#include <librealsense2/rs.hpp>

int main()
{
    try
    {
        // 创建 RealSense 上下文，便于管理设备和资源
        rs2::context ctx;

        // 检查是否有设备连接
        auto device = ctx.query_devices();
        if (device.size() == 0)
        {
            std::cout << "No devices found!\n";
            return -1;
        }

        // 获取设备信息并打印
        rs2::device dev = device[0];
        std::cout << "Hello from Realsense!\n";
        std::cout << "Device's Name: " << dev.get_info(RS2_CAMERA_INFO_NAME) << std::endl;
        std::cout << "Device's Serial Number: " << dev.get_info(RS2_CAMERA_INFO_SERIAL_NUMBER) << std::endl;
        std::cout << "Firmware Version: " << dev.get_info(RS2_CAMERA_INFO_FIRMWARE_VERSION) << std::endl;

        // 创建 Config，配置参数
        rs2::config cfg;
        cfg.enable_stream(RS2_STREAM_COLOR, 640, 480, RS2_FORMAT_BGR8, 30);
        cfg.enable_stream(RS2_STREAM_DEPTH, 640, 480, RS2_FORMAT_Z16, 30);

        // 启动 Pipeline
        rs2::pipeline pipe;
        rs2::pipeline_profile profile = pipe.start(cfg);

        std::cout << "Pipeline started!\n";

        while (true)
        {
            rs2::frameset frames = pipe.wait_for_frames();

            rs2::video_frame color_frame = frames.get_color_frame();
            rs2::video_frame depth_frame = frames.get_depth_frame();

            if (depth_frame)
            {
                float depth_meters = depth_frame.get_timestamp();
                std::cout << "Depth meters: " << depth_meters << std::endl;
            }
        }
        pipe.stop();
        std::cout << "Pipeline stopped!\n";
    }
    catch (const rs2::error& e)
    {
        std::cerr << e.what() << std::endl;
    }

    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
