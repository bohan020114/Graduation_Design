/*
 * @Description: 
 * @Author: Bohan Wang
 * @Date: 2024-05-01 14:35:17
 * @LastEditTime: 2024-05-01 14:35:26
 * @LastEditors:  
 */
#ifndef PLOTTING_H
#define PLOTTING_H

#include <SFML/Graphics.hpp>
#include <vector>

class Plotter {
public:
    // 构造函数，传入窗口尺寸和标题
    Plotter(unsigned int width, unsigned int height, const std::string& title)
        : window(width, height, title)
    {
    }

    // 绘制函数，接收横坐标和纵坐标数组，并绘制点
    void plotPoints(const std::vector<float>& xCoords, const std::vector<float>& yCoords) {
        // 主循环，直到窗口关闭
        while (window.isOpen())
        {
            // 处理窗口事件
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            // 清空窗口
            window.clear(sf::Color::White);

            // 绘制点
            sf::CircleShape point(2); // 创建一个半径为2的圆形，表示点
            point.setFillColor(sf::Color::Black);

            // 遍历坐标数组，绘制每个点
            for (size_t i = 0; i < xCoords.size(); ++i)
            {
                point.setPosition(xCoords[i], yCoords[i]); // 设置点的位置
                window.draw(point); // 绘制点
            }

            // 显示绘制的内容
            window.display();
        }
    }

private:
    sf::RenderWindow window; // SFML窗口对象
};

#endif // PLOTTING_H
