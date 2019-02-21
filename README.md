# VSync Lock Bug

**VSync locking FPS at half under high load**

When under a high workload on Mac or Windows, the FPS will clamp to a dramatically lower number (40, 30, 20, etc). This happens when running in fullscreen and VSync is enabled. If VSync is then disabled, the FPS will increase to a much higher number. (How high depends on the workload.)

**Expected result:** FPS might be slightly lower with VSync enabled, but not drop by 19 or 29 additional frames.

By default, VSync is enabled on mac and win32 builds. VSync can be enabled or disabled by calling `glfwSwapInterval(1)` and `glfwSwapInterval(0)` respectively.

![VSync Lock Bug - Test Project](https://user-images.githubusercontent.com/775602/53200328-e60ef180-35e6-11e9-813e-3c0e1103b427.png)

### Environment

Issue found on macOS and win32 builds. (Linux not tested)

- cocos2d-x versions: 
   - 3.17.1
   - 3.13.1
- devices test on:
   - MacBook Pro 15-inch, Mid 2014 (MGXC2LL/A) - macOS 10.12.6
   - MacBook Pro 15-inch, Mid 2014 (MGXC2LL/A) - Windows 10
   - MacPro 2010 - macOS 10.12.6
   - HP Z420 - Windows 10
   - MacBook Pro 15-inch, Mid 2007 - macOS 10.10.5
- developing environments
   - Xcode version: 9.2
   - VS version: 2017 Professional

### Video + Test Code

[Example Video][video] - View at 1080p60
[Test Code Gist][gist] 
[Full Test Project Repo][repo]

### Steps to Reproduce:

May be easiest to run my [test project][repo], but the bug should be reproducible without:

1. Create a fullscreen glView: `GLViewImpl::createWithFullScreen`
2. Display FPS counter: `director->setDisplayStats(true);`
3. Create enough work to tank the FPS. Often it will clamp at 30.
4. Disabled VSync with `glfwSwapInterval(0)` to observe the FPS change.

### Additional Notes

I’ve experienced this bug under many conditions. For example, I was playtesting a game and used Alt+Tab to switch to the Windows desktop. When I returned to the game, the FPS was locked at 30. I’ve also noticed by reducing the workload temporarily, the FPS will sometimes return back to 60. If I briefly pause and then unpause my game while “VSync Locked”, sometimes the FPS will return to 60.

I’ve found [two][issue1] [similar][issue2] issues, but they seem Mac specific or lack details to reproduce. This bug is found across multiple platforms (Mac + Win32) and can be linked to VSync.

### A Theory

It’s my understanding that VSync can block the main thread (by design) when `void glfwSwapBuffers(GLFWwindow* window)` is called. I suspect that this is causing a “feedback loop” with the Cocos2d-x run loop. That Cocos2d-x is waiting too long and skipping a frame, and then that causes the swapBuffer to skip a frame. However I’m unsure yet how to test this theory. (Sorry if this sounds silly. I’m still learning about the Cocos2d-x source.)

[video]: https://www.youtube.com/watch?v=sQGegtezMHI 
[gist]: https://gist.github.com/RustyMoyher/84a9250f0179235b513489e8ca0846ff
[repo]: https://github.com/RustyMoyher/VSyncLockBug
[issue1]: https://github.com/cocos2d/cocos2d-x/issues/16561
[issue2]: https://github.com/cocos2d/cocos2d-x/issues/18053
