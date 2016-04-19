# Unreal Engine 4 NeoFur Plugin Installation

There are two installation options.  You can either install into your engine directory, so that every project using that version of the engine will have access to the plugin - or you can install directly into a specific project, so that only that project will have access the plugin.

#### Project Installation (recommended)
Create a "Plugins" folder in your UE4 Project and copy the "Neoglyphic" directory there.
```
  YourProject/MyProject.uproject
  YourProject/Plugins/Neoglyphic/ 
```

#### Secondary Actions
The NeoFur plugin will be enabled by default.  Additionally when opening your project the first time, our custom .usf shader files will be copied and placed in the proper relative directory. You may receive a dialog asking your approval for this step.

There is a very small amount of base content you can copy out of 
```
	YourProject/Plugins/Neoglyphic/NeoFur/Content/
```
and into your own content directory, if you so desire.  this provides the master material template and a handful of other assets.  The majority of the test assets can be found in our Demo project, downloaded separately.

see https://neofur.torchpad.com/ for more detailed documentation.


# Attributions

1.	The Indie NeoFur PlugIn® uses the Unreal® Engine.  Unreal® is a trademark or registered trademark of Epic Games, Inc. in the United States of America and elsewhere.  Unreal® Engine, Copyright 1998 – 2016, Epic Games, Inc. All rights reserved.  

2.	The Indie NeoFur PlugIn® contains Autodesk® FBX® files developed by Autodesk, Inc.  Copyright 2014 Autodesk, Inc.  All rights reserved.  Such files are provided “as is” and Autodesk, Inc. disclaims any and all warranties, whether express or implied, including without limitation the implied warranties of merchantability, fitness for a particular purpose and non-infringement of third party rights.  In no event shall Autodesk, Inc. be liable for any direct, indirect, incidental, special, exemplary, or consequential damages (including, but not limited to, procurement of substitute goods or services; loss of use, data, or profits; or business interruption) however caused and on any theory of liability, whether in contract, strict liability, or tort (including negligence or otherwise) arising in any way out of such files.  

---

NeoFur PlugIn® is developed by Neoglyphic Entertainment, Inc. Patent Pending. 

Copyright (c) 2016 Neoglyphic Entertainment, Inc. All rights reserved.
