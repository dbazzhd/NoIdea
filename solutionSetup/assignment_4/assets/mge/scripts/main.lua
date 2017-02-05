------------------------------------------------------------------------------------------------------------------------
--														start()
------------------------------------------------------------------------------------------------------------------------
function start ()
	say ("Welcome to this adventure. Find a coin!")

	--textField1 = createTextField("defaultBold.otf", 40)
	--setText(textField1, "New Text")

	camera = getMainCamera()
	setPosition (camera, 0, 15, 0)
	setRotation(camera,90,0,0)

	ground = createObject("ground", 0, -0.05, 0, "purple")
	setScale(ground, 21, 0.1, 21)
	--setOrbit(camera, ground)

	player = createObject("player", 0, 0.6, -5, "red")
	--setScale(player, 1,2,3)
	--setFollowee(camera, player)
	--say(getPosition(player, "X"))
	
	wall1 = createObject("wall", -10, 0.5, 0, "black")
	wall2 = createObject("wall", -9, 0.5, 0, "black")
	wall3 = createObject("wall", -8, 0.5, 0, "black")
	wall4 = createObject("wall", -7, 0.5, 0, "black")
	wall5 = createObject("wall", -6, 0.5, 0, "black")
	wall6 = createObject("wall", -5, 0.5, 0, "black")
	wall7 = createObject("wall", -4, 0.5, 0, "black")
	wall8 = createObject("wall", -3, 0.5, 0, "black")
	wall9 = createObject("wall", -2, 0.5, 0, "black")
	wall13 = createObject("wall", 2, 0.5, 0, "black")
	wall14 = createObject("wall", 3, 0.5, 0, "black")
	wall15 = createObject("wall", 4, 0.5, 0, "black")
	wall16 = createObject("wall", 5, 0.5, 0, "black")
	wall17 = createObject("wall", 6, 0.5, 0, "black")
	wall18 = createObject("wall", 7, 0.5, 0, "black")
	wall19 = createObject("wall", 8, 0.5, 0, "black")
	wall20 = createObject("wall", 9, 0.5, 0, "black")
	wall21 = createObject("wall", 10, 0.5, 0, "black")



	coin = createObject("coin", -5, 0.5, 5, "yellow")
	key = createObject ("key", 5, 0.5, -5, "grey")

	door1 = createObject ("door", -1, 0.5, 0, "brown")
	door2 = createObject ("door", 0, 0.5, 0, "brown")
	door3 = createObject ("door", 1, 0.5, 0, "brown")
	 say("DONE")

	--[[setMainCharacter(player);

	addListener (player, key, "onPlayerKeyCollide")
	addListener (player, coin, "onPlayerCoinCollide")

	addListener (player, door1, "onPlayerDoorCollide")
	addListener (player, door2, "onPlayerDoorCollide")
	addListener (player, door3, "onPlayerDoorCollide")

	addListener (player, wall1, "onPlayerWallCollide")
	addListener (player, wall2, "onPlayerWallCollide")
	addListener (player, wall3, "onPlayerWallCollide")
	addListener (player, wall4, "onPlayerWallCollide")
	addListener (player, wall5, "onPlayerWallCollide")
	addListener (player, wall6, "onPlayerWallCollide")
	addListener (player, wall7, "onPlayerWallCollide")
	addListener (player, wall8, "onPlayerWallCollide")
	addListener (player, wall9, "onPlayerWallCollide")
	addListener (player, wall13, "onPlayerWallCollide")
	addListener (player, wall14, "onPlayerWallCollide")
	addListener (player, wall15, "onPlayerWallCollide")
	addListener (player, wall16, "onPlayerWallCollide")
	addListener (player, wall17, "onPlayerWallCollide")
	addListener (player, wall18, "onPlayerWallCollide")
	addListener (player, wall19, "onPlayerWallCollide")
	addListener (player, wall20, "onPlayerWallCollide")
	addListener (player, wall21, "onPlayerWallCollide")]]--
	
	hasKey = false
end
------------------------------------------------------------------------------------------------------------------------
--														onPlayerDoorCollide()
------------------------------------------------------------------------------------------------------------------------
function onPlayerDoorCollide(player,door)
	if hasKey == true then
		destroy(door)
	end
	if hasKey== false then
		say("Game: You need to collect the YELLOW key!")
	end
end
------------------------------------------------------------------------------------------------------------------------
--														onPlayerWallCollide()
------------------------------------------------------------------------------------------------------------------------
function onPlayerWallCollide(player, wall)
	moveBack(player, wall)
end
------------------------------------------------------------------------------------------------------------------------
--														onPlayerKeyCollide()
------------------------------------------------------------------------------------------------------------------------
function onPlayerKeyCollide(player, key)
	say("Game: YELLOW key added to inventory!")
	destroy(key)
	hasKey = true
end
------------------------------------------------------------------------------------------------------------------------
--														onPlayerCoinCollide()
------------------------------------------------------------------------------------------------------------------------
function onPlayerCoinCollide(player, coin)
	if hasKey == true then
		say("Game: Game complete!")
		destroy(coin);
	else
		say("Game: You need to find the YELLOW key and walk through the door first!")
	end
end
