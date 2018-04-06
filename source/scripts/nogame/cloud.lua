Cloud = class("Cloud")

local cloudsDir = love.filesystem.getDirectoryItems("graphics/clouds")
local cloudImage = {}
for i = 1, #cloudsDir do
	cloudImage[i] = love.graphics.newImage("graphics/clouds/" .. cloudsDir[i])
end

function Cloud:init(i, x, y)
	self.image = cloudImage[i]

	self.x = x
	self.y = y
end

function Cloud:draw()
	love.graphics.draw(self.image, self.x, self.y)
end