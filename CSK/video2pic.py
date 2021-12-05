import cv2
import os


def video2pic(pic_path, video_path):
    # print(filename)
    cnt = 0
    dnt = 0
    if os.path.exists(pic_path):
        pass
    else:
        os.mkdir(pic_path)
    cap = cv2.VideoCapture(video_path)  # 读入视频
    each_pic = 10
    while True:
        # get a frame
        ret, image = cap.read()
        if image is None:
            break
        # show a frame

        w = image.shape[1]
        h = image.shape[0]
        if (cnt % each_pic) == 0:
            cv2.imencode('.jpg', image)[1].tofile(pic_path + '/p' + str(dnt+1) + '.jpg')
            # cv2.imwrite('C:/Users/JiangHuiQi/Desktop/pic/' + str(filename) + '/' + str(dnt) + '.jpg', image) #含中文路径，不可行
            print(pic_path + '/p' + str(dnt+1) + '.jpg')
            dnt = dnt + 1
            # cv2.namedWindow('sliding_slice',0)
            # cv2.imshow('image', image)
            # cv2.waitKey(1000)
        cnt = cnt + 1
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break
    cap.release()

pic_path = '/Users/xuming.lxm/Workplace/CSK/my_pic2'
video_path = '/Users/xuming.lxm/Workplace/CSK/my_pic2/normal_video.mp4'
video2pic(pic_path, video_path)